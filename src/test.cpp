/*
 * test.cpp
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
static int graphs = 1000;

static inline bool generateAndCompare() {
  IntArrayGraphMapNeighbourHood G;
  
  // [2, max_order] vertices, weights in [1, max_weight]
  generateGraph(G, rand()%(max_order - 1) + 2, max_weight);
  
  IntAllPairsShortestPaths res1(G, IntDijkstra());
  IntAllPairsShortestPaths res2(G, IntSerialDeltaStepping());
  IntAllPairsShortestPaths res3(G, IntParallelDeltaStepping());
  
  return (res1 == res2) && (res2 == res3);
}

void test(int argc, char** argv) {
  srand(time(nullptr));
  int delta = 1;
  if (argc >= 2) {
    sscanf(argv[1], "%d", &delta);
  }
  DeltaStepping::delta(&delta);
  DeltaStepping::initRelaxations();
  int n_threads = 1;
  if (argc >= 3) {
    sscanf(argv[2], "%d", &n_threads);
  }
  ThreadManager::init(n_threads);
  
  int i = 0;
  for (; i < graphs && generateAndCompare(); i++);
  if (i < graphs) {
    printf("erro! algum algoritmo nao esta correto\n");
  }
  
  ThreadManager::close();
  DeltaStepping::closeRelaxations();
}
