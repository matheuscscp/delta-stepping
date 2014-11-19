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

typedef AllPairsShortestPaths<int, 0x7fffffff>  IntAllPairsShortestPaths;
typedef SerialDijkstra<int, 0x7fffffff>         IntDijkstra;
typedef SerialDeltaStepping<int, 0x7fffffff>    IntSerialDeltaStepping;
typedef ParallelDeltaStepping<int, 0x7fffffff>  IntParallelDeltaStepping;

} // namespace graph

#endif /* GRAPHALGORITHMS_HPP_ */
