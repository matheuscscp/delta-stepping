/*
 * Helpers.hpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#ifndef HELPERS_HPP_
#define HELPERS_HPP_

#include "Graph.hpp"

void scanUndirectedGraph(graph::IntGraph& G, FILE* fp);
void scanDirectedGraph(graph::IntGraph& G, FILE* fp);
void printDirectedGraph(const graph::IntGraph& G, FILE* fp);

/**
 * Generates loop-free weighted undirected graphs without multiple edges, using
 * a uniform distribution.
 * G: container
 * N: number of vertices
 * max_weight: will generate weights in [1, max_weight]
 */
void generateGraph(graph::IntGraph& G, int N, int max_weight);

#endif /* HELPERS_HPP_ */
