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

static int delta = 1;
static float dt;
static uint64_t relaxations;

static inline void readAndRun() {
  IntArrayGraphMapNeighbourHood G;
  scanDirectedGraph(G, stdin);
  int source;
  scanf("%d", &source);
  
  int* dist = new int[G.order() + 1];
  Stopwatch sw;
  IntParallelDeltaStepping delta_stepping(delta);
  delta_stepping.run(G, source, dist);
  dt = sw.time();
  relaxations = delta_stepping.relaxations();
  delete[] dist;
}

void test(int argc, char** argv) {
  if (argc >= 2) {
    sscanf(argv[1], "%d", &delta);
  }
  int n_threads = 1;
  if (argc >= 3) {
    sscanf(argv[2], "%d", &n_threads);
  }
  
  srand(time(nullptr));
  ThreadManager::init(n_threads);
  
  Stopwatch sw;
  readAndRun();
  float total_time = sw.time();
  printf("%f s\n", dt);
  printf("time with input: %f s\n", total_time);
  printf("total relaxations: %lu\n", relaxations);
  
  ThreadManager::close();
}
