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

static int threshold = 1000;
static float delta = 1.0f/300;
static float dt;
static uint64_t relaxations;

static inline void readAndRun(FILE* fp) {
  FloatArrayGraphMapNeighbourhood G;
  scanDirectedGraph(G, fp);
  int source;
  fscanf(fp, "%d", &source);
  
  float* dist = new float[G.order() + 1];
  Stopwatch sw;
  FloatParallelDeltaStepping delta_stepping(threshold, delta);
  delta_stepping.run(G, source, dist);
  dt = sw.time();
  relaxations = delta_stepping.relaxations();
  
  float* distd = new float[G.order() + 1];
  FloatDijkstra dijk;
  dijk.run(G, source, distd);
  
  for (int v = 1; v <= G.order(); v++) {
    if (dist[v] != distd[v]) {
      printf("erro: %f %f\n", dist[v], distd[v]);
      break;
    }
  }
  
  delete[] dist;
  delete[] distd;
}

void test(int argc, char** argv) {
  int n_threads = 1;
  if (argc >= 2) {
    sscanf(argv[1], "%d", &n_threads);
  }
  if (argc >= 3) {
    sscanf(argv[2], "%d", &threshold);
  }
  if (argc >= 4) {
    sscanf(argv[3], "%f", &delta);
  }
  
  srand(time(nullptr));
  ThreadManager::init(n_threads);
  
  FILE* fp = fopen(argv[4], "r");
  Stopwatch sw;
  readAndRun(fp);
  float total_time = sw.time();
  if (fp != stdin) {
    fclose(fp);
  }
  printf("%f s\n", dt);
  printf("time with input: %f s\n", total_time);
  printf("total relaxations: %lu\n", relaxations);
  
  ThreadManager::close();
}
