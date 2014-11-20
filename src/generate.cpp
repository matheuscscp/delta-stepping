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
  int order, max_weight; float edge_prob;
  scanf("%d %d %f", &order, &max_weight, &edge_prob);
  graph::IntArrayGraphMapNeighbourHood G;
  generateGraph(G, order, max_weight, edge_prob);
  printDirectedGraph(G, stdout);
}
