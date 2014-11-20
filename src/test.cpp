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

static inline float readAndRun() {
  IntArrayGraphMapNeighbourHood G;
  scanDirectedGraph(G, stdin);
  
  int* dist = new int[G.order() + 1];
  Stopwatch sw;
  IntParallelDeltaStepping().run(G, 1, dist);
  float dt = sw.time();
  delete[] dist;
  
  return dt;
}

void test(int argc, char** argv) {
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
  
  srand(time(nullptr));
  DeltaStepping::init(&delta);
  ThreadManager::init(n_threads);
  
  Stopwatch sw;
  printf("%f\n", readAndRun());
  printf("%f %lu\n", sw.time(), DeltaStepping::relaxations());
  
  ThreadManager::close();
  DeltaStepping::close();
}
