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

static int max_order = 20;
static int max_weight = 50;
static float edge_prob = 0.8f;
static int graphs = 100;

static inline bool generateAndCompare() {
  IntArrayGraphMapNeighbourHood G;
  
  // [2, max_order] vertices, weights in [1, max_weight]
  generateGraph(G, rand()%(max_order - 1) + 2, max_weight, edge_prob);
  
  IntAllPairsShortestPaths res1(G, IntDijkstra());
  IntAllPairsShortestPaths res2(G, IntSerialDeltaStepping(1));
  IntAllPairsShortestPaths res3(G, IntParallelDeltaStepping(1));
  
  return (res1 == res2) && (res2 == res3);
}

void correctness(int argc, char** argv) {
  srand(time(nullptr));
  ThreadManager::init(1);
  
  int i = 0;
  for (; i < graphs && generateAndCompare(); i++);
  if (i < graphs) {
    printf("error! some algorithm is wrong\n");
  }
  
  ThreadManager::close();
}
