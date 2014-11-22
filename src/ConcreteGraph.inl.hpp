/*
 * ConcreteGraph.inl.hpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#ifndef CONCRETEGRAPH_INL_HPP_
#define CONCRETEGRAPH_INL_HPP_

namespace graph {

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
ArrayNeighbourhood<Weight, Vertex, nullvertex, Size>::Iterator::Iterator(Edge<Weight, Vertex, nullvertex>* ptr) : Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator(nullptr, nullptr), ptr(ptr) {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
bool ArrayNeighbourhood<Weight, Vertex, nullvertex, Size>::Iterator::operator!=(const typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator& other) const {
  return ptr != ((ArrayNeighbourhood::Iterator&)other).ptr;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Edge<Weight, Vertex, nullvertex> ArrayNeighbourhood<Weight, Vertex, nullvertex, Size>::Iterator::operator*() {
  return *ptr;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator& ArrayNeighbourhood<Weight, Vertex, nullvertex, Size>::Iterator::operator++() {
  ptr++;
  return *this;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
ArrayNeighbourhood<Weight, Vertex, nullvertex, Size>::ArrayNeighbourhood() : size_(0), data(new Edge<Weight, Vertex, nullvertex>[0]), degree_(0) {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
ArrayNeighbourhood<Weight, Vertex, nullvertex, Size>::~ArrayNeighbourhood() {
  delete[] data;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator ArrayNeighbourhood<Weight, Vertex, nullvertex, Size>::begin() const {
  return typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator(new Iterator(data), new Iterator(data + size_));
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator ArrayNeighbourhood<Weight, Vertex, nullvertex, Size>::end() const {
  return typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator(new Iterator(data + size_), new Iterator(data + size_));
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Edge<Weight, Vertex, nullvertex> ArrayNeighbourhood<Weight, Vertex, nullvertex, Size>::operator[](Vertex v) const {
  return data[v - 1];
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Size ArrayNeighbourhood<Weight, Vertex, nullvertex, Size>::degree() const {
  return degree_;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
void ArrayNeighbourhood<Weight, Vertex, nullvertex, Size>::resize(Size new_size) {
  Edge<Weight, Vertex, nullvertex>* tmp = new Edge<Weight, Vertex, nullvertex>[new_size];
  degree_ = 0;
  for (Size i = 0; i < new_size && i < size_; i++) {
    Weight w = data[i].weight;
    tmp[i].weight = w;
    if (w < Weight(0x7fffffff)) {
      degree_++;
    }
  }
  size_ = new_size;
  delete[] data;
  data = tmp;
  for (Size i = 0; i < size_; i++) {
    data[i].vertex = i + 1;
  }
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
void ArrayNeighbourhood<Weight, Vertex, nullvertex, Size>::edge(Vertex v, Weight w) {
  if (data[v - 1].weight < Weight(0x7fffffff) && w == Weight(0x7fffffff)) {
    degree_--;
  }
  else if (data[v - 1].weight == Weight(0x7fffffff) && w < Weight(0x7fffffff)) {
    degree_++;
  }
  data[v - 1].weight = w;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
MapNeighbourhood<Weight, Vertex, nullvertex, Size>::Iterator::Iterator(typename std::map<Vertex, Edge<Weight, Vertex, nullvertex>>::const_iterator mapit) : Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator(nullptr, nullptr), mapit(mapit) {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
bool MapNeighbourhood<Weight, Vertex, nullvertex, Size>::Iterator::operator!=(const typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator& other) const {
  return mapit != ((Iterator&)other).mapit;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Edge<Weight, Vertex, nullvertex> MapNeighbourhood<Weight, Vertex, nullvertex, Size>::Iterator::operator*() {
  return mapit->second;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator& MapNeighbourhood<Weight, Vertex, nullvertex, Size>::Iterator::operator++() {
  mapit++;
  return *this;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator MapNeighbourhood<Weight, Vertex, nullvertex, Size>::begin() const {
  return typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator(new Iterator(data.begin()), new Iterator(data.end()));
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator MapNeighbourhood<Weight, Vertex, nullvertex, Size>::end() const {
  return typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator(new Iterator(data.end()), new Iterator(data.end()));
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Edge<Weight, Vertex, nullvertex> MapNeighbourhood<Weight, Vertex, nullvertex, Size>::operator[](Vertex v) const {
  return data.at(v);
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Size MapNeighbourhood<Weight, Vertex, nullvertex, Size>::degree() const {
  return data.size();
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
void MapNeighbourhood<Weight, Vertex, nullvertex, Size>::resize(Size new_size) {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
void MapNeighbourhood<Weight, Vertex, nullvertex, Size>::edge(Vertex v, Weight w) {
  if (w == Weight(0x7fffffff)) {
    data.erase(v);
  }
  else {
    Edge<Weight, Vertex, nullvertex>& data_v = data[v];
    data_v.vertex = v;
    data_v.weight = w;
  }
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
ArrayGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::Iterator::Iterator(NeighbourhoodType* ptr) : Graph<Weight, Vertex, nullvertex, Size>::Iterator(nullptr), ptr(ptr) {
  
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
bool ArrayGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::Iterator::operator!=(const typename Graph<Weight, Vertex, nullvertex, Size>::Iterator& other) const {
  return ptr != ((Iterator&)other).ptr;
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, Vertex, nullvertex, Size>& ArrayGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::Iterator::operator*() {
  return *ptr;
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
typename Graph<Weight, Vertex, nullvertex, Size>::Iterator& ArrayGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::Iterator::operator++() {
  ptr++;
  return *this;
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
ArrayGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::ArrayGraph() : order_(0), data(new NeighbourhoodType[0]) {
  
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
ArrayGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::~ArrayGraph() {
  delete[] data;
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
typename Graph<Weight, Vertex, nullvertex, Size>::Iterator ArrayGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::begin() const {
  return typename Graph<Weight, Vertex, nullvertex, Size>::Iterator(new Iterator(data));
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
typename Graph<Weight, Vertex, nullvertex, Size>::Iterator ArrayGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::end() const {
  return typename Graph<Weight, Vertex, nullvertex, Size>::Iterator(new Iterator(data + order_));
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, Vertex, nullvertex, Size>& ArrayGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::operator[](Vertex v) const {
  return data[v - 1];
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Size ArrayGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::order() const {
  return order_;
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
void ArrayGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::order(Size new_order) {
  order_ = new_order;
  delete[] data;
  data = new NeighbourhoodType[order_];
  for (Size i = 0; i < order_; i++) {
    data[i].vertex = i + 1;
    data[i].resize(order_);
  }
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
MapGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::Iterator::Iterator(typename std::map<Vertex, NeighbourhoodType>::const_iterator mapit) : Graph<Weight, Vertex, nullvertex, Size>::Iterator(nullptr), mapit(mapit) {
  
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
bool MapGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::Iterator::operator!=(const typename Graph<Weight, Vertex, nullvertex, Size>::Iterator& other) const {
  return mapit != ((Iterator&)other).mapit;
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, Vertex, nullvertex, Size>& MapGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::Iterator::operator*() {
  return (Neighbourhood<Weight, Vertex, nullvertex, Size>&)mapit->second;
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
typename Graph<Weight, Vertex, nullvertex, Size>::Iterator& MapGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::Iterator::operator++() {
  mapit++;
  return *this;
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
typename Graph<Weight, Vertex, nullvertex, Size>::Iterator MapGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::begin() const {
  return typename Graph<Weight, Vertex, nullvertex, Size>::Iterator(new Iterator(data.begin()));
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
typename Graph<Weight, Vertex, nullvertex, Size>::Iterator MapGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::end() const {
  return typename Graph<Weight, Vertex, nullvertex, Size>::Iterator(new Iterator(data.end()));
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, Vertex, nullvertex, Size>& MapGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::operator[](Vertex v) const {
  return (Neighbourhood<Weight, Vertex, nullvertex, Size>&)data.at(v);
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
Size MapGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::order() const {
  return data.size();
}

template <class NeighbourhoodType, typename Weight, typename Vertex, Vertex nullvertex, typename Size>
void MapGraph<NeighbourhoodType, Weight, Vertex, nullvertex, Size>::order(Size new_order) {
  data.clear();
  for (Vertex u = 1; u <= new_order; u++) {
    data[u].vertex = u;
    data[u].resize(new_order);
  }
}

} // namespace graph

#endif /* CONCRETEGRAPH_INL_HPP_ */
