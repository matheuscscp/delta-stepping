/*
 * GraphAlgorithms.hpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#ifndef GRAPHALGORITHMS_HPP_
#define GRAPHALGORITHMS_HPP_

#include "AllPairsShortestPaths.hpp"
#include "Dijkstra.hpp"
#include "DeltaStepping.hpp"

namespace graph {

typedef AllPairsShortestPaths<int, 0x7fffffff> IntAllPairsShortestPaths;

} // namespace graph

#include "GraphAlgorithms.inl.hpp"

#endif /* GRAPHALGORITHMS_HPP_ */
