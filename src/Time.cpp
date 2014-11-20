/*
 * Time.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: matheus
 */

#include "Time.hpp"

Stopwatch::Stopwatch() {
  gettimeofday(&i, nullptr);
}

void Stopwatch::start() {
  gettimeofday(&i, nullptr);
}

float Stopwatch::time() const {
  timeval f;
  gettimeofday(&f, nullptr);
  return (f.tv_sec - i.tv_sec) + (f.tv_usec - i.tv_usec)/1000000.0f;
}
