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

class Thread {
  private:
    bool free;
    sem_t sem;
    pthread_cond_t cond;
    pthread_mutex_t cond_mutex;
    pthread_t p_thread;
    function<void()> job;
  public:
    Thread();
    ~Thread();
    bool isFree() const;
    bool work(function<void()> job);
    void wait();
  private:
    void work();
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
  bool freed = work([]() {});
  if (freed) {
    pthread_join(p_thread, nullptr);
  }
  else {
    pthread_kill(p_thread, SIGKILL);
  }
  sem_destroy(&sem);
  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&cond_mutex);
}

bool Thread::isFree() const {
  return free;
}

bool Thread::work(function<void()> job) {
  if (!free) {
    return false;
  }
  free = false;
  this->job = job;
  sem_post(&sem);
  return true;
}

void Thread::wait() {
  pthread_mutex_lock(&cond_mutex);
  if (free) {
    pthread_mutex_unlock(&cond_mutex);
    return;
  }
  pthread_cond_wait(&cond, &cond_mutex);
  pthread_mutex_unlock(&cond_mutex);
}

void Thread::work() {
  sem_wait(&sem);
  job();
  pthread_mutex_lock(&cond_mutex);
  free = true;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&cond_mutex);
}

void* Thread::func(void* arg) {
  Thread& thread = *((Thread*)arg);
  while (n_threads > 0) {
    thread.work();
  }
  return nullptr;
}

void ThreadManager::init(int n_th) {
  n_threads = n_th;
  threads = new Thread[n_threads];
}

void ThreadManager::close() {
  n_threads = 0;
  delete[] threads;
}

int ThreadManager::nThreads() {
  return n_threads;
}

bool ThreadManager::isFree(int id) {
  return threads[id].isFree();
}

bool ThreadManager::work(int id, function<void()> job) {
  return threads[id].work(job);
}

void ThreadManager::wait(int id) {
  threads[id].wait();
}
