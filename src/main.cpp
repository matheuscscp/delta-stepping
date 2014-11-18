/*
 * main.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: Pimenta
 */

#include <cstdlib>
#include <ctime>

#include "Dijkstra.hpp"
#include "DeltaStepping.hpp"

using namespace std;
using namespace graph;

static Size max_order = 20;
static Weight max_weight = 50;
static Size graphs = 1000;

static inline bool generateAndCompare() {
  ArrayGraph<MapNeighbourhood> G;
  
  // [2, maxN] vertices, weights in [1, maxWeight]
  generateGraph(G, rand()%(max_order - 1) + 2, max_weight);
  
  AllPairsShortestPaths res1(G, &dijkstra, "dijkstra");
  AllPairsShortestPaths res2(G, &serial_deltaStepping, "serial ds");
  AllPairsShortestPaths res3(G, &parallel_deltaStepping, "parallel ds");
  
  return (res1 == res2) && (res2 == res3);
}

int main(int argc, char** argv) {
  
  srand(time(nullptr));
  
  Size i = 0;
  for (; i < graphs && generateAndCompare(); i++);
  if (i < graphs) {
    printf("erro! algum algoritmo nao esta correto\n");
  }
  
  return 0;
}
