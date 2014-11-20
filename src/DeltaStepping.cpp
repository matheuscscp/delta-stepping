/*
 * DeltaStepping.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: Pimenta
 */

#include "DeltaStepping.hpp"

#include <pthread.h>

static pthread_mutex_t relaxations_mutex;

namespace graph {

void* DeltaStepping::delta_ = nullptr;
uint64_t DeltaStepping::relaxations_ = 0;

void DeltaStepping::init(void* delta) {
  pthread_mutex_init(&relaxations_mutex, nullptr);
  delta_ = delta;
}

void DeltaStepping::close() {
  pthread_mutex_destroy(&relaxations_mutex);
}

void DeltaStepping::incRelaxations() {
  pthread_mutex_lock(&relaxations_mutex);
  relaxations_++;
  pthread_mutex_unlock(&relaxations_mutex);
}

uint64_t DeltaStepping::relaxations() {
  return relaxations_;
}

} // namespace graph
