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

static int n_threads = 1;
static int delta = 1;
static int max_weight = 100;
static int order = 100;

static inline float generateAndRun() {
  // [2, max_order] vertices, weights in [1, max_weight]
  IntArrayGraphMapNeighbourHood G;
  generateGraph(G, order, max_weight);
  
  int* dist = new int[G.order() + 1];
  Stopwatch sw;
  IntParallelDeltaStepping().run(G, 1, dist);
  float dt = sw.time();
  delete[] dist;
  
  return dt;
}

void test(int argc, char** argv) {
  Stopwatch sw;
  
  srand(time(nullptr));
  if (argc >= 2) {
    sscanf(argv[1], "%d", &n_threads);
  }
  if (argc >= 3) {
    sscanf(argv[2], "%d", &delta);
  }
  if (argc >= 4) {
    sscanf(argv[3], "%d", &max_weight);
  }
  if (argc >= 5) {
    sscanf(argv[4], "%d", &order);
  }
  DeltaStepping::delta(&delta);
  DeltaStepping::initRelaxations();
  ThreadManager::init(n_threads);
  
  printf("%f\n", generateAndRun());
  printf("relaxations: %lu\n", DeltaStepping::relaxations());
  
  ThreadManager::close();
  DeltaStepping::closeRelaxations();
  
  printf("%f\n", sw.time());
}
