/*
 * Dijkstra.inl.hpp
 *
 *  Created on: Nov 19, 2014
 *      Author: Pimenta
 */

#ifndef DIJKSTRA_INL_HPP_
#define DIJKSTRA_INL_HPP_

#include <queue>

namespace graph {

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
void SerialDijkstra<Weight, INFINITE, Vertex, nullvertex, Size>::run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist) {
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

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
std::string SerialDijkstra<Weight, INFINITE, Vertex, nullvertex, Size>::name() const {
  return "Dijkstra (serial)";
}

} // namespace graph

#endif /* DIJKSTRA_INL_HPP_ */
