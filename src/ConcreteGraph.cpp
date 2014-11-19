/*
 * ConcreteGraph.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#include "ConcreteGraph.hpp"

using namespace std;

namespace graph {

ArrayNeighbourhood::Iterator::Iterator(Edge<int, 0x7fffffff>* ptr) :
Neighbourhood<int, 0x7fffffff>::Iterator(nullptr, nullptr), ptr(ptr)
{
  
}

bool ArrayNeighbourhood::Iterator::operator!=(
  const Neighbourhood<int, 0x7fffffff>::Iterator& other
) const {
  return ptr != ((ArrayNeighbourhood::Iterator&)other).ptr;
}

Edge<int, 0x7fffffff> ArrayNeighbourhood::Iterator::operator*() {
  return *ptr;
}

Neighbourhood<int, 0x7fffffff>::Iterator& ArrayNeighbourhood::Iterator::operator++() {
  ptr++;
  return *this;
}

ArrayNeighbourhood::ArrayNeighbourhood() :
size_(0), data(new Edge<int, 0x7fffffff>[0]), degree_(0)
{
  
}

ArrayNeighbourhood::~ArrayNeighbourhood() {
  delete[] data;
}

Neighbourhood<int, 0x7fffffff>::Iterator ArrayNeighbourhood::begin() const {
  return Neighbourhood<int, 0x7fffffff>::Iterator(
    new Iterator(data), new Iterator(data + size_)
  );
}

Neighbourhood<int, 0x7fffffff>::Iterator ArrayNeighbourhood::end() const {
  return Neighbourhood<int, 0x7fffffff>::Iterator(
    new Iterator(data + size_), new Iterator(data + size_)
  );
}

Edge<int, 0x7fffffff> ArrayNeighbourhood::operator[](int v) const {
  return data[v - 1];
}

int ArrayNeighbourhood::degree() const {
  return degree_;
}

void ArrayNeighbourhood::resize(int new_size) {
  Edge<int, 0x7fffffff>* tmp = new Edge<int, 0x7fffffff>[new_size];
  degree_ = 0;
  for (int i = 0; i < new_size && i < size_; i++) {
    int w = data[i].weight;
    tmp[i].weight = w;
    if (w < 0x7fffffff) {
      degree_++;
    }
  }
  size_ = new_size;
  delete[] data;
  data = tmp;
  for (int i = 0; i < size_; i++) {
    data[i].vertex = i + 1;
  }
}

void ArrayNeighbourhood::edge(int v, int w) {
  if (data[v - 1].weight < 0x7fffffff && w == 0x7fffffff) {
    degree_--;
  }
  else if (data[v - 1].weight == 0x7fffffff && w < 0x7fffffff) {
    degree_++;
  }
  data[v - 1].weight = w;
}

MapNeighbourhood::Iterator::Iterator(map<int, Edge<int, 0x7fffffff>>::const_iterator mapit) :
Neighbourhood<int, 0x7fffffff>::Iterator(nullptr, nullptr), mapit(mapit)
{
  
}

bool MapNeighbourhood::Iterator::operator!=(
  const Neighbourhood<int, 0x7fffffff>::Iterator& other
) const {
  return mapit != ((Iterator&)other).mapit;
}

Edge<int, 0x7fffffff> MapNeighbourhood::Iterator::operator*() {
  return mapit->second;
}

Neighbourhood<int, 0x7fffffff>::Iterator& MapNeighbourhood::Iterator::operator++() {
  mapit++;
  return *this;
}

Neighbourhood<int, 0x7fffffff>::Iterator MapNeighbourhood::begin() const {
  return Neighbourhood<int, 0x7fffffff>::Iterator(
    new Iterator(data.begin()), new Iterator(data.end())
  );
}

Neighbourhood<int, 0x7fffffff>::Iterator MapNeighbourhood::end() const {
  return Neighbourhood<int, 0x7fffffff>::Iterator(
    new Iterator(data.end()), new Iterator(data.end())
  );
}

Edge<int, 0x7fffffff> MapNeighbourhood::operator[](int v) const {
  return data.at(v);
}

int MapNeighbourhood::degree() const {
  return data.size();
}

void MapNeighbourhood::edge(int v, int w) {
  if (w == 0x7fffffff) {
    data.erase(v);
  }
  else {
    Edge<int, 0x7fffffff>& data_v = data[v];
    data_v.vertex = v;
    data_v.weight = w;
  }
}

} // namespace graph
