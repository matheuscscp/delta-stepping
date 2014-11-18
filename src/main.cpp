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
static int maxN = 20;
static Weight maxWeight = 50;
static int maxGs = 1000;

static inline bool generateAndCompare() {
  ArrayGraph<ArrayNeighbourhood> G;
  
  // [2, maxN] vertices, weights in [1, maxWeight]
  generateGraph(G, rand()%(maxN - 1) + 2, maxWeight);
  
  APSP dijkstraResult(G, &dijkstra);
  APSP deltaResult(G, &serial_deltaStepping);
  
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
