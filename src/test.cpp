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
#include "Time.hpp"
#include "GraphAlgorithms.hpp"
#include "ThreadManager.hpp"

using namespace std;
using namespace graph;

static inline float readAndRun() {
  IntArrayGraphMapNeighbourHood G;
  scanDirectedGraph(G, stdin);
  int source;
  scanf("%d", &source);
  
  int* dist = new int[G.order() + 1];
  Stopwatch sw;
  IntParallelDeltaStepping().run(G, source, dist);
  float dt = sw.time();
  delete[] dist;
  
  return dt;
}

void test(int argc, char** argv) {
  int delta = 1;
  if (argc >= 2) {
    sscanf(argv[1], "%d", &delta);
  }
  int n_threads = 1;
  if (argc >= 3) {
    sscanf(argv[2], "%d", &n_threads);
  }
  
  srand(time(nullptr));
  DeltaStepping::init(&delta);
  ThreadManager::init(n_threads);
  
  Stopwatch sw;
  printf("%f s\n", readAndRun());
  printf("time with input: %f s\n", sw.time());
  printf("total relaxations: %lu\n", DeltaStepping::relaxations());
  
  ThreadManager::close();
  DeltaStepping::close();
}
