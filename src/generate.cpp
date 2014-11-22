/*
 * generate.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: matheus
 */

#include <cstdio>

#include "ConcreteGraph.hpp"
#include "Helpers.hpp"

void generate(int argc, char** argv) {
  int order; float edge_prob; int source;
  scanf("%d %f %d", &order, &edge_prob, &source);
  graph::FloatArrayGraphMapNeighbourhood G;
  generateGraph(G, order, edge_prob);
  printDirectedGraph(G, stdout);
  printf("%d\n", source);
}
