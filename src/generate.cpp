/*
 * generate.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: matheus
 */

#include <cstdio>

#include "ConcreteGraph.hpp"
#include "Helpers.hpp"

void genER(graph::FloatGraph& G) {
  int order; float edge_prob;
  scanf("%d %f", &order, &edge_prob);
  generateERGraph(G, order, edge_prob);
}

void genSW(graph::FloatGraph& G) {
  int order; int d;
  scanf("%d %d", &order, &d);
  generateSWGraph(G, order, d);
}

void generate(int argc, char** argv) {
  srand(time(nullptr));
  graph::FloatArrayGraphMapNeighbourhood G;
  int gtype;
  scanf("%d", &gtype);
  switch (gtype) {
    case 1: genER(G); break;
    case 2: genSW(G); break;
    default:          break;
  }
  int source;
  scanf("%d", &source);
  printDirectedGraph(G, stdout);
  printf("%d\n", source);
}
