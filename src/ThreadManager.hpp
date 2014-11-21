/*
 * ThreadManager.hpp
 *
 *  Created on: Nov 19, 2014
 *      Author: matheus
 */

#ifndef THREADMANAGER_HPP_
#define THREADMANAGER_HPP_

#include <memory>
#include <functional>
#include <list>

class ThreadManager {
  public:
    static void init(int n_threads);
    static void close();
    static int nthreads();
};

class JobHandle;

class Job {
  private:
    std::shared_ptr<JobHandle> handle;
  public:
    Job(std::function<void()> job);
    ~Job();
    static void dispatch(std::function<void()> job);
};

class JobPool {
  private:
    std::list<std::shared_ptr<JobHandle>> handles;
  public:
    ~JobPool();
    void dispatch(std::function<void()> job);
};

#endif /* THREADMANAGER_HPP_ */
