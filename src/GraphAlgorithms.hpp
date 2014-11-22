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

typedef AllPairsShortestPaths<int>    IntAllPairsShortestPaths;
typedef SerialDijkstra<int>           IntDijkstra;
typedef SerialDeltaStepping<int>      IntSerialDeltaStepping;
typedef ParallelDeltaStepping<int>    IntParallelDeltaStepping;
typedef AllPairsShortestPaths<float>  FloatAllPairsShortestPaths;
typedef SerialDijkstra<float>         FloatDijkstra;
typedef SerialDeltaStepping<float>    FloatSerialDeltaStepping;
typedef ParallelDeltaStepping<float>  FloatParallelDeltaStepping;

} // namespace graph

#endif /* GRAPHALGORITHMS_HPP_ */
