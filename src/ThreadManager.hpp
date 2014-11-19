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
    static int nThreads();
    static bool isFree(int id);
    static bool work(int id, std::function<void()> job);
    static void wait(int id);
};

#endif /* THREADMANAGER_HPP_ */
