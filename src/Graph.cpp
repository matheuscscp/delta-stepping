/*
 * Graph.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: Pimenta
 */

#include <cstdlib>

#include "Graph.hpp"

using namespace std;

Graph scanUndirectedGraph(FILE* fp) {
  Graph G;
  
  int N, M;
  fscanf(fp, "%d %d", &N, &M);
  
  // creating vertices
  for (Vertex v = 1; v <= N; v++) {
    G[v];
  }
  
  // reading edges
  for (int m = 0; m < M; m++) {
    Vertex u, v;
    Weight w;
    fscanf(fp, "%d %d %d", &u, &v, &w);
    G[u][v] = w;
    G[v][u] = w;
  }
  
  return G;
}

Graph scanDirectedGraph(FILE* fp) {
  Graph G;
  
  int N, M;
  fscanf(fp, "%d %d", &N, &M);
  
  // creating vertices
  for (Vertex v = 1; v <= N; v++) {
    G[v];
  }
  
  // reading edges
  for (int m = 0; m < M; m++) {
    Vertex source, target;
    Weight w;
    fscanf(fp, "%d %d %d", &source, &target, &w);
    G[source][target] = w;
  }
  
  return G;
}

void printDirectedGraph(FILE* fp, const Graph& G) {
  int M = 0;
  for (auto& kv : G) {
    M += int(kv.second.size());
  }
  fprintf(fp, "%d %d\n", int(G.size()), M);
  for (auto& kv : G) {
    for (auto& kv2 : kv.second) {
      fprintf(fp, "%d %d %d\n", kv.first, kv2.first, kv2.second);
    }
  }
}

Graph generateGraph(int N, Weight maxWeight) {
  Graph G;
  
  // creating vertices
  for (Vertex v = 1; v <= N; v++) {
    G[v];
  }
  
  // creating edges
  int maxM = (N*(N - 1))/2;
  int M = rand()%(maxM + 1);
  for (int m = 0; m < M; m++) {
    Vertex u = rand()%N + 1, v = u + rand()%(N - 1) + 1;
    if (v > N) {
      v -= N;
    }
    map<Vertex, Weight>& G_u = G[u];
    if (G_u.find(v) != G_u.end()) {
      m--;
    }
    else {
      Weight w = rand()%maxWeight + 1;
      G_u[v] = w;
      G[v][u] = w;
    }
  }
  
  return G;
}
