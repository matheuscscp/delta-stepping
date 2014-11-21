/*
 * ThreadManager.cpp
 *
 *  Created on: Nov 19, 2014
 *      Author: matheus
 */

#include "ThreadManager.hpp"

#include <queue>
#include <semaphore.h>
#include <pthread.h>
#include <signal.h>

using namespace std;

// =============================================================================
// Private classes
// =============================================================================

class JobHandle {
  private:
    bool done;
    function<void()> job;
    pthread_cond_t cond;
    pthread_mutex_t cond_mutex;
  public:
    JobHandle(function<void()> job);
    ~JobHandle();
    void run();
    void wait();
};

class Thread {
  private:
    pthread_t p_thread;
  public:
    Thread();
    ~Thread();
  private:
    static void* func(void*);
};

// =============================================================================
// Private globals
// =============================================================================

static int n_threads;
static Thread* threads;
static queue<shared_ptr<JobHandle>> jobs;
static pthread_mutex_t jobs_mutex;
static sem_t jobs_sem;

// =============================================================================
// ThreadManager
// =============================================================================

void ThreadManager::init(int n_th) {
  pthread_mutex_init(&jobs_mutex, nullptr);
  sem_init(&jobs_sem, 0, 0);
  n_threads = n_th;
  threads = new Thread[n_threads];
}

void ThreadManager::close() {
  int n_th = n_threads;
  n_threads = 0;
  for (int i = 0; i < n_th; i++) {
    sem_post(&jobs_sem);
  }
  delete[] threads;
  pthread_mutex_destroy(&jobs_mutex);
  sem_destroy(&jobs_sem);
}

int ThreadManager::nthreads() {
  return n_threads;
}

// =============================================================================
// JobHandle
// =============================================================================

JobHandle::JobHandle(function<void()> job) : done(false), job(job) {
  pthread_cond_init(&cond, nullptr);
  pthread_mutex_init(&cond_mutex, nullptr);
}

JobHandle::~JobHandle() {
  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&cond_mutex);
}

void JobHandle::run() {
  job();
  pthread_mutex_lock(&cond_mutex);
  done = true;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&cond_mutex);
}

void JobHandle::wait() {
  pthread_mutex_lock(&cond_mutex);
  if (!done) {
    pthread_cond_wait(&cond, &cond_mutex);
  }
  pthread_mutex_unlock(&cond_mutex);
}

// =============================================================================
// Job
// =============================================================================

Job::Job(function<void()> job) : handle(new JobHandle(job)) {
  pthread_mutex_lock(&jobs_mutex);
  jobs.push(handle);
  pthread_mutex_unlock(&jobs_mutex);
  sem_post(&jobs_sem);
}

Job::~Job() {
  handle->wait();
}

void Job::dispatch(function<void()> job) {
  pthread_mutex_lock(&jobs_mutex);
  jobs.emplace(new JobHandle(job));
  pthread_mutex_unlock(&jobs_mutex);
  sem_post(&jobs_sem);
}

// =============================================================================
// JobPool
// =============================================================================

JobPool::~JobPool() {
  for (auto& handle : handles) {
    handle->wait();
  }
}

void JobPool::dispatch(function<void()> job) {
  handles.emplace_back(new JobHandle(job));
  pthread_mutex_lock(&jobs_mutex);
  jobs.push(handles.back());
  pthread_mutex_unlock(&jobs_mutex);
  sem_post(&jobs_sem);
}

// =============================================================================
// Thread functions
// =============================================================================

Thread::Thread() {
  pthread_create(&p_thread, nullptr, &func, nullptr);
}

Thread::~Thread() {
  pthread_join(p_thread, nullptr);
}

void* Thread::func(void*) {
  while (n_threads > 0) {
    sem_wait(&jobs_sem);
    if (n_threads > 0) {
      pthread_mutex_lock(&jobs_mutex);
      shared_ptr<JobHandle> handle(jobs.front()); jobs.pop();
      pthread_mutex_unlock(&jobs_mutex);
      handle->run();
    }
  }
  return nullptr;
}
