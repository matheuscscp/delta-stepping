/*
 * ThreadManager.cpp
 *
 *  Created on: Nov 19, 2014
 *      Author: matheus
 */

#include "ThreadManager.hpp"

#include <semaphore.h>
#include <pthread.h>
#include <signal.h>

using namespace std;

struct Thread {
  bool free;
  sem_t sem;
  pthread_cond_t cond;
  pthread_mutex_t cond_mutex;
  pthread_t p_thread;
  function<void()> job;
  Thread();
  ~Thread();
  static void* func(void* arg);
};

static int n_threads;
static Thread* threads;

Thread::Thread() : free(true) {
  sem_init(&sem, 0, 0);
  pthread_cond_init(&cond, nullptr);
  pthread_mutex_init(&cond_mutex, nullptr);
  pthread_create(&p_thread, nullptr, &func, (void*)this);
}

Thread::~Thread() {
  pthread_kill(p_thread, SIGKILL);
  sem_destroy(&sem);
  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&cond_mutex);
}

void* Thread::func(void* arg) {
  Thread& thread = *((Thread*)arg);
  while (true) {
    sem_wait(&thread.sem);
    thread.job();
    pthread_mutex_lock(&thread.cond_mutex);
    thread.free = true;
    pthread_cond_broadcast(&thread.cond);
    pthread_mutex_unlock(&thread.cond_mutex);
  }
  return nullptr;
}

void ThreadManager::init(int n_th) {
  n_threads = n_th;
  threads = new Thread[n_threads];
}

void ThreadManager::close() {
  delete[] threads;
}

int ThreadManager::nThreads() {
  return n_threads;
}

bool ThreadManager::isFree(int id) {
  return threads[id].free;
}

bool ThreadManager::work(int id, function<void()> job) {
  Thread& thread = threads[id];
  if (!thread.free) {
    return false;
  }
  thread.free = false;
  thread.job = job;
  sem_post(&thread.sem);
  return true;
}

void ThreadManager::wait(int id) {
  Thread& thread = threads[id];
  pthread_mutex_lock(&thread.cond_mutex);
  if (thread.free) {
    pthread_mutex_unlock(&thread.cond_mutex);
    return;
  }
  pthread_cond_wait(&thread.cond, &thread.cond_mutex);
  pthread_mutex_unlock(&thread.cond_mutex);
}
