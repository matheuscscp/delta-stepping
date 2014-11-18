/*
 * Dijkstra.hpp
 *
 *  Created on: Nov 5, 2014
 *      Author: Pimenta
 */

#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_

#include <queue>

#include "Graph.hpp"

template <typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
void dijkstra(const graph::Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist) {
  using namespace graph;
  
  Size N = G.order();
  for (Vertex v = 1; v <= N; v++) {
    dist[v] = INFINITE;
  }
  dist[source] = 0;
  std::priority_queue<Edge<Weight, INFINITE, Vertex, nullvertex>> Q;
  Q.push(Edge<Weight, INFINITE, Vertex, nullvertex>(source, 0));
  
  for (Vertex i = 0; !Q.empty() && i < N; i++) {
    Edge<Weight, INFINITE, Vertex, nullvertex> edge = Q.top();
    Q.pop();
    
    if (edge.weight > dist[edge.vertex]) {
      i--;
      continue;
    }
    
    auto& u = G[edge.vertex];
    for (auto v : u) {
      Weight alt = edge.weight + v.weight;
      if (alt < dist[v.vertex]) {
        dist[v.vertex] = alt;
        Q.push(Edge<Weight, INFINITE, Vertex, nullvertex>(v.vertex, alt));
      }
    }
  }
}

#endif /* DIJKSTRA_HPP_ */
