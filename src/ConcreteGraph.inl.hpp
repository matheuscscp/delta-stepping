/*
 * ConcreteGraph.inl.hpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#ifndef CONCRETEGRAPH_INL_HPP_
#define CONCRETEGRAPH_INL_HPP_

namespace graph {

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
ArrayNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::Iterator(Edge<Weight, INFINITE, Vertex, nullvertex>* ptr) : Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator(nullptr, nullptr), ptr(ptr) {
  
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
bool ArrayNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::operator!=(const typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& other) const {
  return ptr != ((ArrayNeighbourhood::Iterator&)other).ptr;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Edge<Weight, INFINITE, Vertex, nullvertex> ArrayNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::operator*() {
  return *ptr;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& ArrayNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::operator++() {
  ptr++;
  return *this;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
ArrayNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::ArrayNeighbourhood() : size_(0), data(new Edge<Weight, INFINITE, Vertex, nullvertex>[0]), degree_(0) {
  
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
ArrayNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::~ArrayNeighbourhood() {
  delete[] data;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator ArrayNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::begin() const {
  return typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator(new Iterator(data), new Iterator(data + size_));
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator ArrayNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::end() const {
  return typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator(new Iterator(data + size_), new Iterator(data + size_));
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Edge<Weight, INFINITE, Vertex, nullvertex> ArrayNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::operator[](Vertex v) const {
  return data[v - 1];
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Size ArrayNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::degree() const {
  return degree_;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
void ArrayNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::resize(Size new_size) {
  Edge<Weight, INFINITE, Vertex, nullvertex>* tmp = new Edge<Weight, INFINITE, Vertex, nullvertex>[new_size];
  degree_ = 0;
  for (Size i = 0; i < new_size && i < size_; i++) {
    Weight w = data[i].weight;
    tmp[i].weight = w;
    if (w < INFINITE) {
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

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
void ArrayNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::edge(Vertex v, Vertex w) {
  if (data[v - 1].weight < INFINITE && w == INFINITE) {
    degree_--;
  }
  else if (data[v - 1].weight == INFINITE && w < INFINITE) {
    degree_++;
  }
  data[v - 1].weight = w;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
MapNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::Iterator(typename std::map<Vertex, Edge<Weight, INFINITE, Vertex, nullvertex>>::const_iterator mapit) : Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator(nullptr, nullptr), mapit(mapit) {
  
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
bool MapNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::operator!=(const typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& other) const {
  return mapit != ((Iterator&)other).mapit;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Edge<Weight, INFINITE, Vertex, nullvertex> MapNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::operator*() {
  return mapit->second;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& MapNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::operator++() {
  mapit++;
  return *this;
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator MapNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::begin() const {
  return typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator(new Iterator(data.begin()), new Iterator(data.end()));
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator MapNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::end() const {
  return typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator(new Iterator(data.end()), new Iterator(data.end()));
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Edge<Weight, INFINITE, Vertex, nullvertex> MapNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::operator[](Vertex v) const {
  return data.at(v);
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Size MapNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::degree() const {
  return data.size();
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
void MapNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::resize(Size new_size) {
  
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
void MapNeighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::edge(Vertex v, Vertex w) {
  if (w == INFINITE) {
    data.erase(v);
  }
  else {
    Edge<Weight, INFINITE, Vertex, nullvertex>& data_v = data[v];
    data_v.vertex = v;
    data_v.weight = w;
  }
}

template <class NeighbourhoodType, typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
ArrayGraph<NeighbourhoodType, Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::Iterator(NeighbourhoodType* ptr) : Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator(nullptr), ptr(ptr) {
  
}

template <class NeighbourhoodType, typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
bool ArrayGraph<NeighbourhoodType, Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::operator!=(const typename Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& other) const {
  return ptr != ((Iterator&)other).ptr;
}

template <class NeighbourhoodType, typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>& ArrayGraph<NeighbourhoodType, Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::operator*() {
  return *ptr;
}

template <class NeighbourhoodType, typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
typename Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& ArrayGraph<NeighbourhoodType, Weight, INFINITE, Vertex, nullvertex, Size>::Iterator::operator++() {
  ptr++;
  return *this;
}

template <class NeighbourhoodType, typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
ArrayGraph<NeighbourhoodType, Weight, INFINITE, Vertex, nullvertex, Size>::ArrayGraph() : order_(0), data(new NeighbourhoodType[0]) {
  
}

template <class NeighbourhoodType, typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
ArrayGraph<NeighbourhoodType, Weight, INFINITE, Vertex, nullvertex, Size>::~ArrayGraph() {
  delete[] data;
}

template <class NeighbourhoodType, typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
typename Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator ArrayGraph<NeighbourhoodType, Weight, INFINITE, Vertex, nullvertex, Size>::begin() const {
  return typename Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator(new Iterator(data));
}

template <class NeighbourhoodType, typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
typename Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator ArrayGraph<NeighbourhoodType, Weight, INFINITE, Vertex, nullvertex, Size>::end() const {
  return typename Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator(new Iterator(data + order_));
}

template <class NeighbourhoodType, typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>& ArrayGraph<NeighbourhoodType, Weight, INFINITE, Vertex, nullvertex, Size>::operator[](Vertex v) const {
  return data[v - 1];
}

template <class NeighbourhoodType, typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
Size ArrayGraph<NeighbourhoodType, Weight, INFINITE, Vertex, nullvertex, Size>::order() const {
  return order_;
}

template <class NeighbourhoodType, typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
void ArrayGraph<NeighbourhoodType, Weight, INFINITE, Vertex, nullvertex, Size>::order(Size new_order) {
  order_ = new_order;
  delete[] data;
  data = new NeighbourhoodType[order_];
  for (Size i = 0; i < order_; i++) {
    data[i].vertex = i + 1;
    data[i].resize(order_);
  }
}

} // namespace graph

#endif /* CONCRETEGRAPH_INL_HPP_ */
