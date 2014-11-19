/*
 * AllPairsShortestPaths.inl.hpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#ifndef ALLPAIRSSHORTESTPATHS_INL_HPP_
#define ALLPAIRSSHORTESTPATHS_INL_HPP_

namespace graph {

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
AllPairsShortestPaths<Weight, INFINITE, Vertex, nullvertex, Size>::AllPairsShortestPaths(
  const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G,
  const SSSPAlgorithm<Weight, INFINITE, Vertex, nullvertex, Size>& ssspfunc
) : order(G.order()), result(new Weight*[order + 1]) {
  for (Vertex u = 1; u <= order; u++) {
    result[u] = new Weight[order + 1];
  }
  Weight* shortest_path_tree = new Weight[order + 1];
  for (auto& u : G) {
    ((SSSPAlgorithm<Weight, INFINITE, Vertex, nullvertex, Size>&)ssspfunc).run(G, u.vertex, shortest_path_tree);
    for (auto& v : G) {
      result[u.vertex][v.vertex] = shortest_path_tree[v.vertex];
    }
  }
  delete[] shortest_path_tree;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
AllPairsShortestPaths<Weight, INFINITE, Vertex, nullvertex, Size>::~AllPairsShortestPaths() {
  for (Vertex u = 1; u <= order; u++) {
    delete[] result[u];
  }
  delete[] result;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
bool AllPairsShortestPaths<Weight, INFINITE, Vertex, nullvertex, Size>::operator==(const AllPairsShortestPaths& other) const {
  if (order != other.order) {
    return false;
  }
  for (Vertex source = 1; source <= order; source++) {
    for (Vertex target = 1; target <= order; target++) {
      if (result[source][target] != other.result[source][target]) {
        return false;
      }
    }
  }
  return true;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
bool AllPairsShortestPaths<Weight, INFINITE, Vertex, nullvertex, Size>::operator!=(const AllPairsShortestPaths& other) const {
  if (order != other.order) {
    return true;
  }
  for (Vertex source = 1; source <= order; source++) {
    for (Vertex target = 1; target <= order; target++) {
      if (result[source][target] != other.result[source][target]) {
        return true;
      }
    }
  }
  return false;
}

} // namespace graph

#endif /* ALLPAIRSSHORTESTPATHS_INL_HPP_ */
