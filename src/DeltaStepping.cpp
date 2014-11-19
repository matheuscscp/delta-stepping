/*
 * DeltaStepping.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: Pimenta
 */

#include "DeltaStepping.hpp"

#include <pthread.h>

namespace graph {

void* DeltaStepping::delta_ = nullptr;
uint64_t DeltaStepping::relaxations_ = 0;
pthread_mutex_t relaxations_mutex;

void DeltaStepping::delta(void* new_delta) {
  delta_ = new_delta;
}

void DeltaStepping::initRelaxations() {
  pthread_mutex_init(&relaxations_mutex, nullptr);
}

uint64_t DeltaStepping::relaxations() {
  return relaxations_;
}

void DeltaStepping::clearRelaxations() {
  relaxations_ = 0;
}

void DeltaStepping::incRelaxations() {
  pthread_mutex_lock(&relaxations_mutex);
  relaxations_++;
  pthread_mutex_unlock(&relaxations_mutex);
}

} // namespace graph
