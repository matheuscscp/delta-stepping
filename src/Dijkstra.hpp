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

inline Weight dijkstra(const Graph& G, Vertex source, Vertex target) {
  struct Path {
    Vertex v;
    Weight dist;
    Path(Vertex v, Weight dist) : v(v), dist(dist) {
      
    }
    bool operator<(const Path& other) const {
      return dist > other.dist;
    }
  };
  
  Weight* dist = new Weight[G.size() + 1];
  for (Vertex v = 1; v <= Vertex(G.size()); v++) {
    dist[v] = INF;
  }
  dist[source] = 0;
  std::priority_queue<Path> Q;
  Q.push(Path(source, 0));
  
  while (!Q.empty()) {
    Path edge = Q.top();
    Q.pop();
    
    if (edge.v == target) break;
    if (edge.dist > dist[edge.v]) continue;
    
    const std::map<Vertex, Weight>& u = G.at(edge.v);
    for (auto& kv : u) {
      Weight alt = edge.dist + kv.second;
      if (alt < dist[kv.first]) {
        dist[kv.first] = alt;
        Q.push(Path(kv.first, alt));
      }
    }
  }
  
  Weight dist_target = dist[target];
  delete[] dist;
  return dist_target;
}

#endif /* DIJKSTRA_HPP_ */
