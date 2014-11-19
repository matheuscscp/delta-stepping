/*
 * DeltaStepping.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: Pimenta
 */

#include "DeltaStepping.hpp"

namespace graph {

void* DeltaStepping::delta_ = nullptr;
uint64_t DeltaStepping::relaxations_ = 0;

void DeltaStepping::delta(void* new_delta) {
  delta_ = new_delta;
}

uint64_t DeltaStepping::relaxations() {
  return relaxations_;
}

void DeltaStepping::clearRelaxations() {
  relaxations_ = 0;
}

void DeltaStepping::incRelaxations() {
  relaxations_++;
}

} // namespace graph
