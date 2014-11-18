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

inline void dijkstra(const Graph& G, Vertex source, Weight* dist) {
  Size N = G.order();
  for (Vertex v = 1; v <= N; v++) {
    dist[v] = INFINITE;
  }
  dist[source] = 0;
  std::priority_queue<Edge> Q;
  Q.push(Edge(source, 0));
  
  for (Vertex i = 0; !Q.empty() && i < N; i++) {
    Edge edge = Q.top();
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
        Q.push(Edge(v.vertex, alt));
      }
    }
  }
}

#endif /* DIJKSTRA_HPP_ */
