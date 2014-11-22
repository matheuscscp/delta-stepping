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

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
void SerialDijkstra<Weight, Vertex, nullvertex, Size>::run(const Graph<Weight, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist) {
  Size N = G.order();
  for (Vertex v = 1; v <= N; v++) {
    dist[v] = Weight(0x7fffffff);
  }
  dist[source] = 0;
  std::priority_queue<Edge<Weight, Vertex, nullvertex>> Q;
  Q.push(Edge<Weight, Vertex, nullvertex>(source, 0));
  
  for (Size i = 0; !Q.empty() && i < N; i++) {
    Edge<Weight, Vertex, nullvertex> edge = Q.top();
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
        Q.push(Edge<Weight, Vertex, nullvertex>(v.vertex, alt));
      }
    }
  }
}

} // namespace graph

#endif /* DIJKSTRA_INL_HPP_ */
