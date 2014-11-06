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

inline Weight* dijkstra(const Graph& G, Vertex source) {
  struct Path {
    Vertex v;
    Weight dist;
    Path(Vertex v, Weight dist) : v(v), dist(dist) {
      
    }
    bool operator<(const Path& other) const {
      return dist > other.dist;
    }
  };
  
  Vertex N = int(G.size());
  Weight* dist = new Weight[N + 1];
  for (Vertex v = 1; v <= N; v++) {
    dist[v] = INF;
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
    
    const std::map<Vertex, Weight>& u = G.at(edge.v);
    for (auto& kv : u) {
      Weight alt = edge.dist + kv.second;
      if (alt < dist[kv.first]) {
        dist[kv.first] = alt;
        Q.push(Path(kv.first, alt));
      }
    }
  }
  
  return dist;
}

#endif /* DIJKSTRA_HPP_ */
