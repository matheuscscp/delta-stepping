/*
 * Graph.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: Pimenta
 */

#include <cstdlib>

#include "Graph.hpp"

using namespace std;

namespace graph {

Edge::Edge(Vertex vertex, Weight weight) : vertex(vertex), weight(weight) {
  
}

bool Edge::operator<(const Edge& other) const {
  return weight > other.weight;
}

Neighbourhood::Iterator::Iterator(Iterator* it, Iterator* itend) :
it(it), itend(itend)
{
  if (it == nullptr) {
    return;
  }
  while (
    this->it->operator!=(*(this->itend)) &&
    this->it->operator*().weight == INFINITE
  ) {
    this->it->operator++();
  }
}

Neighbourhood::Iterator::~Iterator() {
  
}

bool Neighbourhood::Iterator::operator!=(const Iterator& other) const {
  return it->operator!=(*other.it);
}

Edge Neighbourhood::Iterator::operator*() {
  return it->operator*();
}

Neighbourhood::Iterator& Neighbourhood::Iterator::operator++() {
  do {
    it->operator++();
  } while (it->operator!=(*itend) && it->operator*().weight == INFINITE);
  return *this;
}

Neighbourhood::Neighbourhood(Vertex vertex) : vertex(vertex) {
  
}

Neighbourhood::~Neighbourhood() {
  
}

Graph::Iterator::Iterator(Iterator* it) : it(it) {
  
}

Graph::Iterator::~Iterator() {
  
}

bool Graph::Iterator::operator!=(const Iterator& other) const {
  return it->operator!=(*other.it);
}

Neighbourhood& Graph::Iterator::operator*() {
  return it->operator*();
}

Graph::Iterator& Graph::Iterator::operator++() {
  it->operator++();
  return *this;
}

Graph::~Graph() {
  
}

ArrayNeighbourhood::Iterator::Iterator(Edge* ptr) :
Neighbourhood::Iterator(nullptr, nullptr), ptr(ptr)
{
  
}

bool ArrayNeighbourhood::Iterator::operator!=(
  const Neighbourhood::Iterator& other
) const {
  return ptr != ((ArrayNeighbourhood::Iterator&)other).ptr;
}

Edge ArrayNeighbourhood::Iterator::operator*() {
  return *ptr;
}

Neighbourhood::Iterator& ArrayNeighbourhood::Iterator::operator++() {
  ptr++;
  return *this;
}

ArrayNeighbourhood::ArrayNeighbourhood() :
size_(0), data(new Edge[0]), degree_(0)
{
  
}

ArrayNeighbourhood::~ArrayNeighbourhood() {
  delete[] data;
}

Neighbourhood::Iterator ArrayNeighbourhood::begin() const {
  return Neighbourhood::Iterator(
    new Iterator(data), new Iterator(data + size_)
  );
}

Neighbourhood::Iterator ArrayNeighbourhood::end() const {
  return Neighbourhood::Iterator(
    new Iterator(data + size_), new Iterator(data + size_)
  );
}

Edge ArrayNeighbourhood::operator[](Vertex v) const {
  return data[v - 1];
}

Size ArrayNeighbourhood::degree() const {
  return degree_;
}

void ArrayNeighbourhood::resize(Size new_size) {
  Edge* tmp = new Edge[new_size];
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

void ArrayNeighbourhood::edge(Vertex v, Weight w) {
  if (data[v - 1].weight < INFINITE && w == INFINITE) {
    degree_--;
  }
  else if (data[v - 1].weight == INFINITE && w < INFINITE) {
    degree_++;
  }
  data[v - 1].weight = w;
}

MapNeighbourhood::Iterator::Iterator(map<Vertex, Edge>::const_iterator mapit) :
Neighbourhood::Iterator(nullptr, nullptr), mapit(mapit)
{
  
}

bool MapNeighbourhood::Iterator::operator!=(
  const Neighbourhood::Iterator& other
) const {
  return mapit != ((Iterator&)other).mapit;
}

Edge MapNeighbourhood::Iterator::operator*() {
  return mapit->second;
}

Neighbourhood::Iterator& MapNeighbourhood::Iterator::operator++() {
  mapit++;
  return *this;
}

Neighbourhood::Iterator MapNeighbourhood::begin() const {
  return Neighbourhood::Iterator(
    new Iterator(data.begin()), new Iterator(data.end())
  );
}

Neighbourhood::Iterator MapNeighbourhood::end() const {
  return Neighbourhood::Iterator(
    new Iterator(data.end()), new Iterator(data.end())
  );
}

Edge MapNeighbourhood::operator[](Vertex v) const {
  return data.at(v);
}

Size MapNeighbourhood::degree() const {
  return data.size();
}

void MapNeighbourhood::edge(Vertex v, Weight w) {
  if (w == INFINITE) {
    data.erase(v);
  }
  else {
    Edge& data_v = data[v];
    data_v.vertex = v;
    data_v.weight = w;
  }
}

// =============================================================================
// helper functions
// =============================================================================

void scanUndirectedGraph(Graph& G, FILE* fp) {
  int N, M;
  fscanf(fp, "%d %d", &N, &M);
  G.order(N);
  for (int m = 0; m < M; m++) {
    int u, v, w;
    fscanf(fp, "%d %d %d", &u, &v, &w);
    G[u].edge(v, w);
    G[v].edge(u, w);
  }
}

void scanDirectedGraph(Graph& G, FILE* fp) {
  int N, M;
  fscanf(fp, "%d %d", &N, &M);
  G.order(N);
  for (int m = 0; m < M; m++) {
    int source, target, w;
    fscanf(fp, "%d %d %d", &source, &target, &w);
    G[source].edge(target, w);
  }
}

void printDirectedGraph(const Graph& G, FILE* fp) {
  int M = 0;
  for (auto& v : G) {
    M += v.degree();
  }
  fprintf(fp, "%d %d\n", G.order(), M);
  for (auto& source : G) {
    for (auto target : source) {
      fprintf(fp, "%d %d %d\n", source.vertex, target.vertex, target.weight);
    }
  }
}

void generateGraph(Graph& G, int N, Weight maxWeight) {
  G.order(N);
  for (Vertex u = 1; u < N; u++) {
    for (Vertex v = u + 1; v <= N; v++) {
      int tmp = rand()%2;
      if (tmp) {
        Weight w = rand()%maxWeight + 1;
        G[u].edge(v, w);
        G[v].edge(u, w);
      }
    }
  }
}

} // namespace graph
