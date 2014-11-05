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

typedef AllPairsShortestPaths<25> APSP;
static int maxN = 4;
static Weight maxWeight = 50;
static int maxGs = 100;

static inline bool scanAndCompare() {
  Graph G = scanUndirectedGraph(stdin);
  
  APSP dijkstraResult(G, &dijkstra);
  dijkstraResult.print(stdout, "dijkstra");
  APSP deltaResult(G, &deltaStepping);
  deltaResult.print(stdout, "delta stepping");
  
  return dijkstraResult == deltaResult;
}

static inline bool generateAndCompare() {
  // [2, maxN] vertices, weights in [1, maxWeight]
  Graph G = generateGraph(rand()%(maxN - 1) + 2, maxWeight);
  
  APSP dijkstraResult(G, &dijkstra);
  APSP deltaResult(G, &deltaStepping);
  
  return dijkstraResult == deltaResult;
}

int main(int argc, char** argv) {
  
  srand(time(nullptr));
  
  int i = 0;
  for (; i < maxGs && generateAndCompare(); i++);
  if (i < maxGs) {
    printf("erro! nao ta funfando\n");
  }
  
  return 0;
}
