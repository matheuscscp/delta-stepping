/*
 * Helpers.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#include "Helpers.hpp"

#include <cstdio>
#include <cstdlib>

using namespace graph;

void scanUndirectedGraph(IntGraph& G, FILE* fp) {
  int N, M;
  fscanf(fp, "%d %d", &N, &M);
  G.order(N);
  for (int m = 0; m < M; m++) {
    int u, v, w;
    fscanf(fp, "%d %d %d", &u, &v, &w);
    G[u].edge(v, w);
    G[v].edge(u, w);
  }
}

void scanDirectedGraph(IntGraph& G, FILE* fp) {
  int N, M;
  fscanf(fp, "%d %d", &N, &M);
  G.order(N);
  for (int m = 0; m < M; m++) {
    int source, target, w;
    fscanf(fp, "%d %d %d", &source, &target, &w);
    G[source].edge(target, w);
  }
}

void printDirectedGraph(const IntGraph& G, FILE* fp) {
  int M = 0;
  for (auto& v : G) {
    M += v.degree();
  }
  fprintf(fp, "%d %d\n", G.order(), M);
  for (auto& source : G) {
    for (auto target : source) {
      fprintf(fp, "%d %d %d\n", source.vertex, target.vertex, target.weight);
    }
  }
}

void generateGraph(IntGraph& G, int order, int max_weight, float edge_prob) {
  G.order(order);
  for (int u = 1; u < order; u++) {
    for (int v = u + 1; v <= order; v++) {
      float tmp = rand()%1000 + 1.0f;
      if (tmp <= edge_prob*1000) {
        int w = rand()%max_weight + 1;
        G[u].edge(v, w);
        G[v].edge(u, w);
      }
    }
  }
}
