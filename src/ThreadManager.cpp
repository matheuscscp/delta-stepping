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

// =============================================================================
// Thread class
// =============================================================================

class Thread {
  private:
    bool free;
    sem_t sem;
    pthread_cond_t cond;
    pthread_mutex_t cond_mutex;
    pthread_t p_thread;
    function<void()> job;
  public:
    // outside thread functions
    Thread();
    ~Thread();
    bool isfree() const;
    void dispatch(function<void()> job);
    void wait();
  private:
    // inside thread functions
    void work();
    static void* func(void* arg);
};

// =============================================================================
// Private globals
// =============================================================================

static int n_threads;
static Thread* threads;

// =============================================================================
// Thread :: outside thread functions
// =============================================================================

Thread::Thread() : free(true) {
  sem_init(&sem, 0, 0);
  pthread_cond_init(&cond, nullptr);
  pthread_mutex_init(&cond_mutex, nullptr);
  pthread_create(&p_thread, nullptr, &func, (void*)this);
}

Thread::~Thread() {
  if (free) {
    dispatch([]() {});
    pthread_join(p_thread, nullptr);
  }
  else {
    pthread_kill(p_thread, SIGKILL);
  }
  sem_destroy(&sem);
  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&cond_mutex);
}

bool Thread::isfree() const {
  return free;
}

void Thread::dispatch(function<void()> job) {
  free = false;
  this->job = job;
  sem_post(&sem);
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

// =============================================================================
// Thread :: inside thread functions
// =============================================================================

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

// =============================================================================
// ThreadManager
// =============================================================================

void ThreadManager::init(int n_th) {
  n_threads = n_th;
  threads = new Thread[n_threads];
}

void ThreadManager::close() {
  n_threads = 0;
  delete[] threads;
}

int ThreadManager::nthreads() {
  return n_threads;
}

bool ThreadManager::isfree(int id) {
  return threads[id].isfree();
}

void ThreadManager::dispatch(int id, function<void()> job) {
  threads[id].dispatch(job);
}

void ThreadManager::dispatchall(function<void()> job) {
  for (int id = 0; id < n_threads; id++) {
    threads[id].dispatch(job);
  }
}

void ThreadManager::wait(int id) {
  threads[id].wait();
}

void ThreadManager::waitall() {
  for (int id = 0; id < n_threads; id++) {
    threads[id].wait();
  }
}
