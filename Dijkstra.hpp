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

inline Weight dijkstra(const Graph& G, Vertex s, Vertex d) {
  struct Edge {
    Vertex v;
    Weight dist;
    Edge(Vertex v, Weight dist) : v(v), dist(dist) {
      
    }
    bool operator<(const Edge& other) const {
      return dist > other.dist;
    }
  };
  
  Weight* dist = new Weight[G.size() + 1];
  for (Vertex v = 1; v <= Vertex(G.size()); v++) {
    dist[v] = INF;
  }
  dist[s] = 0;
  std::priority_queue<Edge> Q;
  Q.push(Edge(s, 0));
  
  while (!Q.empty()) {
    Edge unode = Q.top();
    Q.pop();
    
    if (unode.v == d) break;
    if (unode.dist > dist[unode.v]) continue;
    
    const std::map<Vertex, Weight>& u = G.at(unode.v);
    for (auto& kv : u) {
      Weight alt = unode.dist + kv.second;
      if (alt < dist[kv.first]) {
        dist[kv.first] = alt;
        Q.push(Edge(kv.first, alt));
      }
    }
  }
  
  Weight w = dist[d];
  delete[] dist;
  return w;
}

#endif /* DIJKSTRA_HPP_ */
