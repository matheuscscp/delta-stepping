/*
 * Time.hpp
 *
 *  Created on: Nov 20, 2014
 *      Author: matheus
 */

#ifndef TIME_HPP_
#define TIME_HPP_

#include <sys/time.h>

class Stopwatch {
  private:
    timeval i;
  public:
    Stopwatch();
    void start();
    float time() const;
};

#endif /* TIME_HPP_ */
