/*
 * Graph.inl.hpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#ifndef GRAPH_INL_HPP_
#define GRAPH_INL_HPP_

#include <map>

namespace graph {

template <class VertexType, typename Weight>
GenericEdge<VertexType, Weight>::GenericEdge(VertexType source, VertexType target, Weight weight) : source(source), target(target), weight(weight) {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex>
Edge<Weight, Vertex, nullvertex>::Edge(Vertex vertex, Weight weight) : vertex(vertex), weight(weight) {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex>
bool Edge<Weight, Vertex, nullvertex>::operator<(const Edge& other) const {
  return weight > other.weight;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator::Iterator(Iterator* it, Iterator* itend) : it(it), itend(itend) {
  if (it == nullptr) {
    return;
  }
  while (this->it->operator!=(*(this->itend)) && this->it->operator*().weight == Weight(0x7fffffff)) {
    this->it->operator++();
  }
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator::~Iterator() {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
bool Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator::operator!=(const Iterator& other) const {
  return it->operator!=(*other.it);
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Edge<Weight, Vertex, nullvertex> Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator::operator*() {
  return it->operator*();
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator& Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator::operator++() {
  do {
    it->operator++();
  } while (it->operator!=(*itend) && it->operator*().weight == Weight(0x7fffffff));
  return *this;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, Vertex, nullvertex, Size>::Neighbourhood(Vertex vertex) : vertex(vertex) {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, Vertex, nullvertex, Size>::~Neighbourhood() {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Graph<Weight, Vertex, nullvertex, Size>::Iterator::Iterator(Iterator* it) : it(it) {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Graph<Weight, Vertex, nullvertex, Size>::Iterator::~Iterator() {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
bool Graph<Weight, Vertex, nullvertex, Size>::Iterator::operator!=(const Iterator& other) const {
  return it->operator!=(*other.it);
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, Vertex, nullvertex, Size>& Graph<Weight, Vertex, nullvertex, Size>::Iterator::operator*() {
  return it->operator*();
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
typename Graph<Weight, Vertex, nullvertex, Size>::Iterator& Graph<Weight, Vertex, nullvertex, Size>::Iterator::operator++() {
  it->operator++();
  return *this;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Graph<Weight, Vertex, nullvertex, Size>::Graph() : maxweight_(0), maxdegree_(0) {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Graph<Weight, Vertex, nullvertex, Size>::~Graph() {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Weight Graph<Weight, Vertex, nullvertex, Size>::maxweight() const {
  return maxweight_;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Size Graph<Weight, Vertex, nullvertex, Size>::maxdegree() const {
  return maxdegree_;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
void Graph<Weight, Vertex, nullvertex, Size>::updatemax() {
  for (auto& u : *this) {
    if (u.degree() > maxdegree_) {
      maxdegree_ = u.degree();
    }
    for (auto v : u) {
      if (v.weight > maxweight_) {
        maxweight_ = v.weight;
      }
    }
  }
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
template <class VertexType>
void Graph<Weight, Vertex, nullvertex, Size>::build(Graph& G, const std::set<VertexType>& vertices, const std::set<GenericEdge<VertexType, Weight>>& edges) {
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

} // namespace graph

#endif /* GRAPH_INL_HPP_ */
