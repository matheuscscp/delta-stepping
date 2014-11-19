/*
 * GraphAlgorithms.inl.hpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#ifndef GRAPHALGORITHMS_INL_HPP_
#define GRAPHALGORITHMS_INL_HPP_

namespace graph {

inline void intDijkstra(const IntGraph& G, int vertex, int* dist) {
  dijkstra<int, 0x7fffffff>(G, vertex, dist);
}

inline void intSerialDeltaStepping(const IntGraph& G, int vertex, int* dist) {
  serialDeltaStepping<int, 0x7fffffff>(G, vertex, dist);
}

inline void intParallelDeltaStepping(const IntGraph& G, int vertex, int* dist) {
  parallelDeltaStepping<int, 0x7fffffff>(G, vertex, dist);
}

} // namespace graph

#endif /* GRAPHALGORITHMS_INL_HPP_ */
