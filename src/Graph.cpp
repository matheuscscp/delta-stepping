/*
 * Graph.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: Pimenta
 */

#include <cstdlib>

#include "Graph.hpp"

using namespace std;

Edge::Edge(Vertex vertex, Weight weight) : vertex(vertex), weight(weight) {
  
}

Neighbourhood::Iterator::Iterator(Iterator* it) : it(it) {
  
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
  it->operator++();
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
Neighbourhood::Iterator(nullptr), ptr(ptr)
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

ArrayNeighbourhood::ArrayNeighbourhood(Size size) :
size_(size), data(new Edge[size]), degree_(0)
{
  for (Size i = 0; i < size; i++) {
    data[i].vertex = i + 1;
  }
}

ArrayNeighbourhood::~ArrayNeighbourhood() {
  delete[] data;
}

Neighbourhood::Iterator ArrayNeighbourhood::begin() const {
  return Neighbourhood::Iterator(new Iterator(data));
}

Neighbourhood::Iterator ArrayNeighbourhood::end() const {
  return Neighbourhood::Iterator(new Iterator(data + size_));
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
      if (target.weight == INFINITE) {
        continue;
      }
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
