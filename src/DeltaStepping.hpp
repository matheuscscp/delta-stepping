/*
 * DeltaStepping.hpp
 *
 *  Created on: Nov 5, 2014
 *      Author: Pimenta
 */

#ifndef DELTASTEPPING_HPP_
#define DELTASTEPPING_HPP_

#include "Graph.hpp"

void serial_deltaStepping(const Graph& G, Vertex source, Weight* dist);

#endif /* DELTASTEPPING_HPP_ */
