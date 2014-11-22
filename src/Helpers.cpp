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

void scanUndirectedGraph(FloatGraph& G, FILE* fp) {
  int N, M;
  fscanf(fp, "%d %d", &N, &M);
  G.order(N);
  for (int m = 0; m < M; m++) {
    int u, v; float w;
    fscanf(fp, "%d %d %f", &u, &v, &w);
    G[u].edge(v, w);
    G[v].edge(u, w);
  }
  G.updatemax();
}

void scanDirectedGraph(FloatGraph& G, FILE* fp) {
  int N, M;
  fscanf(fp, "%d %d", &N, &M);
  G.order(N);
  for (int m = 0; m < M; m++) {
    int source, target; float w;
    fscanf(fp, "%d %d %f", &source, &target, &w);
    G[source].edge(target, w);
  }
  G.updatemax();
}

void printDirectedGraph(const FloatGraph& G, FILE* fp) {
  int M = 0;
  for (auto& v : G) {
    M += v.degree();
  }
  fprintf(fp, "%d %d\n", G.order(), M);
  for (auto& source : G) {
    for (auto target : source) {
      fprintf(fp, "%d %d %f\n", source.vertex, target.vertex, target.weight);
    }
  }
}

void generateGraph(FloatGraph& G, int order, float edge_prob) {
  int d = int(order*edge_prob);
  G.order(order);
  for (int u = 1; u < order; u++) {
    for (int v = u + 1; v <= order; v++) {
      float tmp = (rand()%1001)/1000.0f;
      if (tmp <= edge_prob && G[u].degree() < d) {
        float w = (rand()%1001)/1000.0f;
        G[u].edge(v, w);
      }
      tmp = (rand()%1001)/1000.0f;
      if (tmp <= edge_prob && G[v].degree() < d) {
        float w = (rand()%1001)/1000.0f;
        G[v].edge(u, w);
      }
    }
  }
  G.updatemax();
}
