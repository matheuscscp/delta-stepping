/*
 * Graph.inl.hpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#ifndef GRAPH_INL_HPP_
#define GRAPH_INL_HPP_

namespace graph {

template <class VertexType, typename Weight>
GenericEdge<VertexType, Weight>::GenericEdge(VertexType source, VertexType target, Weight weight) : source(source), target(target), weight(weight) {
  
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex>
Edge<Weight, INFINITE, Vertex, nullvertex>::Edge(Vertex vertex, Weight weight) : vertex(vertex), weight(weight) {
  
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex>
bool Edge<Weight, INFINITE, Vertex, nullvertex>::operator<(const Edge& other) const {
  return weight > other.weight;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::Iterator(Iterator* it, Iterator* itend) : it(it), itend(itend) {
  if (it == nullptr) {
    return;
  }
  while (this->it->operator!=(*(this->itend)) && this->it->operator*().weight == INFINITE) {
    this->it->operator++();
  }
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::~Iterator() {
  
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
bool Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::operator!=(const Iterator& other) const {
  return it->operator!=(*other.it);
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Edge<Weight, INFINITE, Vertex, nullvertex> Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::operator*() {
  return it->operator*();
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::operator++() {
  do {
    it->operator++();
  } while (it->operator!=(*itend) && it->operator*().weight == INFINITE);
  return *this;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Neighbourhood(Vertex vertex) : vertex(vertex) {
  
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::~Neighbourhood() {
  
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::Iterator(Iterator* it) : it(it) {
  
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::~Iterator() {
  
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
bool Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::operator!=(const Iterator& other) const {
  return it->operator!=(*other.it);
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>& Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::operator*() {
  return it->operator*();
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
typename Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::operator++() {
  it->operator++();
  return *this;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Graph<Weight, INFINITE, Vertex, nullvertex, Size>::~Graph() {
  
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
template <class VertexType>
void Graph<Weight, INFINITE, Vertex, nullvertex, Size>::build(Graph& G, const std::set<VertexType>& vertices, const std::set<GenericEdge<VertexType, Weight>>& edges) {
  std::map<VertexType, Vertex> mapping;
  Vertex u = 1;
  G.order(vertices.size());
  for (auto& vertex : vertices) {
    mapping[vertex] = u;
    G[u].vertex = u;
    u++;
  }
  for (auto& edge : edges) {
    G[mapping[edge.source]].edge(mapping[edge.target], edge.weight);
  }
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
AllPairsShortestPaths<Weight, INFINITE, Vertex, nullvertex, Size>::AllPairsShortestPaths(
  const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G,
  std::function<void(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>&, Vertex, Weight*)> spfunc,
  const std::string& funcname
) : order(G.order()), result(new Weight*[order + 1]) {
  for (Vertex u = 1; u <= order; u++) {
    result[u] = new Weight[order + 1];
  }
  Weight* shortest_path_tree = new Weight[order + 1];
  for (auto& u : G) {
    spfunc(G, u.vertex, shortest_path_tree);
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

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
void AllPairsShortestPaths<Weight, INFINITE, Vertex, nullvertex, Size>::print(FILE* fp) const {
  fprintf(fp, "%s:\n", funcname.c_str());
  for (Vertex source = 1; source <= order; source++) {
    for (Vertex target = 1; target <= order; target++) {
      Weight w = result[source][target];
      if (w == INFINITE) {
        fprintf(fp, "  inf ");
      }
      else {
        fprintf(fp, "%5d ", w);
      }
    }
    fprintf(fp, "\n");
  }
}

} // namespace graph

#endif /* GRAPH_INL_HPP_ */
