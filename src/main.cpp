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

static int max_order = 20;
static int max_weight = 50;
static int graphs = 1000;

static inline bool generateAndCompare() {
  ArrayGraph<MapNeighbourhood> G;
  
  // [2, maxN] vertices, weights in [1, maxWeight]
  generateGraph(G, rand()%(max_order - 1) + 2, max_weight);
  
  AllPairsShortestPaths<int, 0x7fffffff> res1(G, &dijkstra<int, 0x7fffffff>, "dijkstra");
  AllPairsShortestPaths<int, 0x7fffffff> res2(G, &serial_deltaStepping<int, 0x7fffffff>, "serial ds");
  AllPairsShortestPaths<int, 0x7fffffff> res3(G, &parallel_deltaStepping<int, 0x7fffffff>, "parallel ds");
  
  return (res1 == res2) && (res2 == res3);
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
