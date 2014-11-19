/*
 * ThreadManager.hpp
 *
 *  Created on: Nov 19, 2014
 *      Author: matheus
 */

#ifndef THREADMANAGER_HPP_
#define THREADMANAGER_HPP_

#include <functional>

class ThreadManager {
  public:
    static void init(int n_threads);
    static void close();
    static int nthreads();
    static bool isfree(int id);
    static void dispatch(int id, std::function<void()> job);
    static void dispatchall(std::function<void()> job);
    static void wait(int id);
    static void waitall();
};

#endif /* THREADMANAGER_HPP_ */
