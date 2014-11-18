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
  struct Path {
    Vertex v;
    Weight dist;
    Path(Vertex v, Weight dist) : v(v), dist(dist) {
      
    }
    bool operator<(const Path& other) const {
      return dist > other.dist;
    }
  };
  
  Size N = G.order();
  for (Vertex v = 1; v <= N; v++) {
    dist[v] = INFINITE;
  }
  dist[source] = 0;
  std::priority_queue<Path> Q;
  Q.push(Path(source, 0));
  
  for (Vertex i = 0; !Q.empty() && i < N; i++) {
    Path edge = Q.top();
    Q.pop();
    
    if (edge.dist > dist[edge.v]) {
      i--;
      continue;
    }
    
    auto& u = G[edge.v];
    for (auto v : u) {
      Weight alt = edge.dist + v.weight;
      if (alt < dist[v.vertex]) {
        dist[v.vertex] = alt;
        Q.push(Path(v.vertex, alt));
      }
    }
  }
}

#endif /* DIJKSTRA_HPP_ */
