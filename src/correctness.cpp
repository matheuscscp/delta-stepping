/*
 * correctness.cpp
 *
 *  Created on: Nov 19, 2014
 *      Author: matheus
 */

#include <cstdlib>
#include <ctime>

#include "ConcreteGraph.hpp"
#include "Helpers.hpp"
#include "GraphAlgorithms.hpp"
#include "ThreadManager.hpp"

using namespace std;
using namespace graph;

static int max_order = 100;
static float edge_prob = 0.5f;
static int graphs = 10;

static inline bool generateAndCompare() {
  FloatArrayGraphMapNeighbourhood G;
  
  // [2, max_order] vertices, weights in [1, max_weight]
  generateGraph(G, rand()%(max_order - 1) + 2, edge_prob);
  
  FloatAllPairsShortestPaths res1(G, FloatDijkstra());
  FloatAllPairsShortestPaths res2(G, FloatSerialDeltaStepping());
  FloatAllPairsShortestPaths res3(G, FloatParallelDeltaStepping(1, 1.0f/50));
  
  return (res1 == res2) && (res2 == res3);
}

void correctness(int argc, char** argv) {
  srand(time(nullptr));
  ThreadManager::init(3);
  
  int i = 0;
  for (; i < graphs && generateAndCompare(); i++);
  if (i < graphs) {
    printf("error! some algorithm is wrong\n");
  }
  
  ThreadManager::close();
}
