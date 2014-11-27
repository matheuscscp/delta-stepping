/*
 * Helpers.hpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#ifndef HELPERS_HPP_
#define HELPERS_HPP_

#include "Graph.hpp"

void scanUndirectedGraph(graph::FloatGraph& G, FILE* fp);
void scanDirectedGraph(graph::FloatGraph& G, FILE* fp);
void printDirectedGraph(const graph::FloatGraph& G, FILE* fp);

/**
 * Generates loop-free weighted undirected graphs without multiple edges, using
 * a uniform distribution.
 */
void generateERGraph(graph::FloatGraph& G, int order, float edge_prob);
void generateSWGraph(graph::FloatGraph& G, int order, int d);

#endif /* HELPERS_HPP_ */
