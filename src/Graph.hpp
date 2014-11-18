/*
 * Graph.hpp
 *
 *  Created on: Nov 4, 2014
 *      Author: Pimenta
 */

#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <memory>
#include <map>
#include <cstdio>

namespace graph {

typedef int Size;
typedef int Vertex;
typedef int Weight;
enum { INFINITE = 0x7fffffff };

class Edge {
  public:
    Vertex vertex;
    Weight weight;
    Edge(Vertex vertex = 0, Weight weight = INFINITE);
    bool operator<(const Edge& other) const;
};

class Neighbourhood {
  public:
    class Iterator : public std::iterator<std::forward_iterator_tag, Edge> {
      private:
        std::shared_ptr<Iterator> it, itend;
      public:
        Iterator(Iterator* it, Iterator* itend);
        virtual ~Iterator();
        virtual bool operator!=(const Iterator& other) const;
        virtual Edge operator*();
        virtual Iterator& operator++();
    };
    Vertex vertex;
    Neighbourhood(Vertex vertex = 0);
    virtual ~Neighbourhood();
    virtual Iterator begin() const = 0;
    virtual Iterator end() const = 0;
    virtual Edge operator[](Vertex v) const = 0;
    virtual Size degree() const = 0;
    virtual void edge(Vertex v, Weight w) = 0;
};

class Graph {
  public:
    class Iterator : public std::iterator<std::forward_iterator_tag, Neighbourhood> {
      private:
        std::shared_ptr<Iterator> it;
      public:
        Iterator(Iterator* it);
        virtual ~Iterator();
        virtual bool operator!=(const Iterator& other) const;
        virtual Neighbourhood& operator*();
        virtual Iterator& operator++();
    };
    virtual ~Graph();
    virtual Iterator begin() const = 0;
    virtual Iterator end() const = 0;
    virtual Neighbourhood& operator[](Vertex v) const = 0;
    virtual Size order() const = 0;
    virtual void order(Size new_order) = 0;
};

class ArrayNeighbourhood : public Neighbourhood {
  public:
    class Iterator : public Neighbourhood::Iterator {
      private:
        Edge* ptr;
      public:
        Iterator(Edge* ptr);
        bool operator!=(const Neighbourhood::Iterator& other) const;
        Edge operator*();
        Neighbourhood::Iterator& operator++();
    };
  private:
    Size size_;
    Edge* data;
    Size degree_;
  public:
    ArrayNeighbourhood();
    ~ArrayNeighbourhood();
    Neighbourhood::Iterator begin() const;
    Neighbourhood::Iterator end() const;
    Edge operator[](Vertex v) const;
    Size degree() const;
    void resize(Size new_size);
    void edge(Vertex v, Weight w);
};

class MapNeighbourhood : public Neighbourhood {
  public:
    class Iterator : public Neighbourhood::Iterator {
      private:
        std::map<Vertex, Edge>::const_iterator mapit;
      public:
        Iterator(std::map<Vertex, Edge>::const_iterator mapit);
        bool operator!=(const Neighbourhood::Iterator& other) const;
        Edge operator*();
        Neighbourhood::Iterator& operator++();
    };
  private:
    std::map<Vertex, Edge> data;
  public:
    Neighbourhood::Iterator begin() const;
    Neighbourhood::Iterator end() const;
    Edge operator[](Vertex v) const;
    Size degree() const;
    void edge(Vertex v, Weight w);
};

template <class NeighbourhoodType>
class ArrayGraph : public Graph {
  public:
    class Iterator : public Graph::Iterator {
      private:
        NeighbourhoodType* ptr;
      public:
        Iterator(NeighbourhoodType* ptr) : Graph::Iterator(nullptr), ptr(ptr) {
          
        }
        bool operator!=(const Graph::Iterator& other) const {
          return ptr != ((Iterator&)other).ptr;
        }
        Neighbourhood& operator*() {
          return *ptr;
        }
        Graph::Iterator& operator++() {
          ptr++;
          return *this;
        }
    };
  private:
    Size order_;
    NeighbourhoodType* data;
  public:
    ArrayGraph() : order_(0), data(new NeighbourhoodType[0]) {
      
    }
    ~ArrayGraph() {
      delete[] data;
    }
    Graph::Iterator begin() const {
      return Graph::Iterator(new Iterator(data));
    }
    Graph::Iterator end() const {
      return Graph::Iterator(new Iterator(data + order_));
    }
    Neighbourhood& operator[](Vertex v) const {
      return data[v - 1];
    }
    Size order() const {
      return order_;
    }
    void order(Size new_order) {
      order_ = new_order;
      delete[] data;
      data = new NeighbourhoodType[order_];
      for (Size i = 0; i < order_; i++) {
        data[i].vertex = i + 1;
      }
    }
};

template <> inline void ArrayGraph<ArrayNeighbourhood>::order(Size new_order) {
  order_ = new_order;
  delete[] data;
  data = new ArrayNeighbourhood[order_];
  for (Size i = 0; i < order_; i++) {
    data[i].vertex = i + 1;
    data[i].resize(order_);
  }
}

template <class NeighbourhoodType>
class MapGraph : public Graph {
  public:
    class Iterator : public Graph::Iterator {
      private:
        typename std::map<Vertex, NeighbourhoodType>::const_iterator mapit;
      public:
        Iterator(
          typename std::map<Vertex, NeighbourhoodType>::const_iterator mapit
        ) : Graph::Iterator(nullptr), mapit(mapit) {
          
        }
        bool operator!=(const Graph::Iterator& other) const {
          return mapit != ((Iterator&)other).mapit;
        }
        Neighbourhood& operator*() {
          return (Neighbourhood&)mapit->second;
        }
        Graph::Iterator& operator++() {
          mapit++;
          return *this;
        }
    };
  private:
    std::map<Vertex, NeighbourhoodType> data;
  public:
    Graph::Iterator begin() const {
      return Graph::Iterator(new Iterator(data.begin()));
    }
    Graph::Iterator end() const {
      return Graph::Iterator(new Iterator(data.end()));
    }
    Neighbourhood& operator[](Vertex v) const {
      return (Neighbourhood&)data.at(v);
    }
    Size order() const {
      return data.size();
    }
    void order(Size new_order) {
      data.clear();
      for (Vertex u = 1; u <= new_order; u++) {
        data[u].vertex = u;
      }
    }
};

template <> inline void MapGraph<ArrayNeighbourhood>::order(Size new_order) {
  data.clear();
  for (Vertex u = 1; u <= new_order; u++) {
    data[u].vertex = u;
    data[u].resize(new_order);
  }
}

class AllPairsShortestPaths {
  private:
    int order;
    Weight** result;
    std::string funcname;
  public:
    AllPairsShortestPaths(
      const Graph& G,
      std::function<void(const Graph&, Vertex, Weight*)> spfunc,
      const std::string& funcname
    );
    ~AllPairsShortestPaths();
    bool operator==(const AllPairsShortestPaths& other) const;
    bool operator!=(const AllPairsShortestPaths& other) const;
    void print(FILE* fp) const;
};

void scanUndirectedGraph(Graph& G, FILE* fp);
void scanDirectedGraph(Graph& G, FILE* fp);
void printDirectedGraph(const Graph& G, FILE* fp);

/**
 * Generates loop-free weighted undirected graphs without multiple edges, using
 * a uniform distribution.
 * G: container
 * N: number of vertices
 * maxWeight: will generate weights in [1, maxWeight]
 */
void generateGraph(Graph& G, int N, Weight maxWeight);

} // namespace graph

#endif /* GRAPH_HPP_ */
