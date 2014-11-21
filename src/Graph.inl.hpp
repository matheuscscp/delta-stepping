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
Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Graph() : maxweight_(0), maxdegree_(0) {
  
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Graph<Weight, INFINITE, Vertex, nullvertex, Size>::~Graph() {
  
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Weight Graph<Weight, INFINITE, Vertex, nullvertex, Size>::maxweight() const {
  return maxweight_;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Size Graph<Weight, INFINITE, Vertex, nullvertex, Size>::maxdegree() const {
  return maxdegree_;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
void Graph<Weight, INFINITE, Vertex, nullvertex, Size>::updatemax() {
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

} // namespace graph

#endif /* GRAPH_INL_HPP_ */
