/*
 * main.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: Pimenta
 */

#include <cstdlib>
#include <ctime>

#include "ConcreteGraph.hpp"
#include "Helpers.hpp"
#include "GraphAlgorithms.hpp"

using namespace std;
using namespace graph;

static int max_order = 20;
static int max_weight = 50;
static int graphs = 1000;

static inline bool generateAndCompare() {
  IntArrayGraphMapNeighbourHood G;
  
  // [2, maxN] vertices, weights in [1, maxWeight]
  generateGraph(G, rand()%(max_order - 1) + 2, max_weight);
  
  IntAllPairsShortestPaths res1(G, IntDijkstra());
  IntAllPairsShortestPaths res2(G, IntSerialDeltaStepping());
  IntAllPairsShortestPaths res3(G, IntParallelDeltaStepping());
  //res1.print(stdout);
  
  return (res1 == res2);
}

int main(int argc, char** argv) {
  
  srand(time(nullptr));
  
  int i = 0;
  for (; i < graphs && generateAndCompare(); i++);
  if (i < graphs) {
    printf("erro! algum algoritmo nao esta correto\n");
  }
  
  return 0;
}
