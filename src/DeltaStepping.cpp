/*
 * DeltaStepping.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: Pimenta
 */

#include "DeltaStepping.hpp"

namespace graph {

void* DeltaStepping::delta_ = nullptr;

void DeltaStepping::delta(void* new_delta) {
  delta_ = new_delta;
}

} // namespace graph
