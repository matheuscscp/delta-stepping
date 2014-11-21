/*
 * Monitor.hpp
 *
 *  Created on: Nov 21, 2014
 *      Author: matheus
 */

#ifndef MONITOR_HPP_
#define MONITOR_HPP_

#include <pthread.h>

template <class T>
class Monitor {
  public:
    class Guard {
      private:
        pthread_mutex_t* mutex;
      public:
        Guard(Monitor<T>& monitor);
        ~Guard();
    };
  private:
    T object;
    pthread_mutex_t mutex;
  public:
    template <typename... Args>
    Monitor(Args&&... args);
    ~Monitor();
    T* operator->();
    template <typename Method, typename... Args>
    typename std::result_of<Method(T*, Args...)>::type call(
      Method method, Args&&... args
    );
};

#include "Monitor.inl.hpp"

#endif /* MONITOR_HPP_ */
