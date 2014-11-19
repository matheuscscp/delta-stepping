/*
 * DeltaStepping.hpp
 *
 *  Created on: Nov 5, 2014
 *      Author: Pimenta
 */

#ifndef DELTASTEPPING_HPP_
#define DELTASTEPPING_HPP_

#include "Graph.hpp"

template <typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
void serialDeltaStepping(const graph::Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist);

template <typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
void parallelDeltaStepping(const graph::Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist);

#include "DeltaStepping.inl.hpp"

#endif /* DELTASTEPPING_HPP_ */
