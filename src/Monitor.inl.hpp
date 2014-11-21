/*
 * Monitor.inl.hpp
 *
 *  Created on: Nov 21, 2014
 *      Author: matheus
 */

#ifndef MONITOR_INL_HPP_
#define MONITOR_INL_HPP_

template <class T>
Monitor<T>::Guard::Guard(Monitor<T>& monitor) : mutex(&monitor.mutex) {
  pthread_mutex_lock(mutex);
}

template <class T>
Monitor<T>::Guard::~Guard() {
  pthread_mutex_unlock(mutex);
}

template <class T>
template <typename... Args>
Monitor<T>::Monitor(Args&&... args) : object(std::forward<Args>(args)...) {
  pthread_mutex_init(&mutex, nullptr);
}

template <class T>
Monitor<T>::~Monitor() {
  pthread_mutex_destroy(&mutex);
}

template <class T>
T* Monitor<T>::operator->() {
  return &object;
}

template <class T>
template <typename Method, typename... Args>
typename std::result_of<Method(T*, Args...)>::type Monitor<T>::call(
  Method method, Args&&... args
) {
  Guard guard(*this);
  return (object.*method)(std::forward<Args>(args)...);
}

#endif /* MONITOR_INL_HPP_ */
