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

/*FIXME
template <typename VertexType, typename WeightType>
class GenericEdge {
  public:
    
};
*/

template <typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0>
class Edge {
  public:
    Vertex vertex;
    Weight weight;
    Edge(Vertex vertex = nullvertex, Weight weight = INFINITE);
    bool operator<(const Edge& other) const;
};

template <typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class Neighbourhood {
  public:
    class Iterator : public std::iterator<std::forward_iterator_tag, Edge<Weight, INFINITE, Vertex, nullvertex>> {
      private:
        std::shared_ptr<Iterator> it, itend;
      public:
        Iterator(Iterator* it, Iterator* itend);
        virtual ~Iterator();
        virtual bool operator!=(const Iterator& other) const;
        virtual Edge<Weight, INFINITE, Vertex, nullvertex> operator*();
        virtual Iterator& operator++();
    };
    Vertex vertex;
    Neighbourhood(Vertex vertex = nullvertex);
    virtual ~Neighbourhood();
    virtual Iterator begin() const = 0;
    virtual Iterator end() const = 0;
    virtual Edge<Weight, INFINITE, Vertex, nullvertex> operator[](Vertex v) const = 0;
    virtual Size degree() const = 0;
    virtual void edge(Vertex v, Weight w) = 0;
};

template <typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class Graph {
  public:
    class Iterator : public std::iterator<std::forward_iterator_tag, Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>> {
      private:
        std::shared_ptr<Iterator> it;
      public:
        Iterator(Iterator* it);
        virtual ~Iterator();
        virtual bool operator!=(const Iterator& other) const;
        virtual Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>& operator*();
        virtual Iterator& operator++();
    };
    virtual ~Graph();
    virtual Iterator begin() const = 0;
    virtual Iterator end() const = 0;
    virtual Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>& operator[](Vertex v) const = 0;
    virtual Size order() const = 0;
    virtual void order(Size new_order) = 0;
    
    //FIXME template <typename VertexType, typename WeightType>
    //FIXME static std::map<> build(Graph& G, const std::set<GenericEdge<VertexType, WeightType>>& edges);
};

class ArrayNeighbourhood : public Neighbourhood<int, 0x7fffffff> {
  public:
    class Iterator : public Neighbourhood::Iterator {
      private:
        Edge<int, 0x7fffffff>* ptr;
      public:
        Iterator(Edge<int, 0x7fffffff>* ptr);
        bool operator!=(const Neighbourhood<int, 0x7fffffff>::Iterator& other) const;
        Edge<int, 0x7fffffff> operator*();
        Neighbourhood<int, 0x7fffffff>::Iterator& operator++();
    };
  private:
    int size_;
    Edge<int, 0x7fffffff>* data;
    int degree_;
  public:
    ArrayNeighbourhood();
    ~ArrayNeighbourhood();
    Neighbourhood<int, 0x7fffffff>::Iterator begin() const;
    Neighbourhood<int, 0x7fffffff>::Iterator end() const;
    Edge<int, 0x7fffffff> operator[](int v) const;
    int degree() const;
    void resize(int new_size);
    void edge(int v, int w);
};

class MapNeighbourhood : public Neighbourhood<int, 0x7fffffff> {
  public:
    class Iterator : public Neighbourhood<int, 0x7fffffff>::Iterator {
      private:
        std::map<int, Edge<int, 0x7fffffff>>::const_iterator mapit;
      public:
        Iterator(std::map<int, Edge<int, 0x7fffffff>>::const_iterator mapit);
        bool operator!=(const Neighbourhood<int, 0x7fffffff>::Iterator& other) const;
        Edge<int, 0x7fffffff> operator*();
        Neighbourhood<int, 0x7fffffff>::Iterator& operator++();
    };
  private:
    std::map<int, Edge<int, 0x7fffffff>> data;
  public:
    Neighbourhood<int, 0x7fffffff>::Iterator begin() const;
    Neighbourhood<int, 0x7fffffff>::Iterator end() const;
    Edge<int, 0x7fffffff> operator[](int v) const;
    int degree() const;
    void edge(int v, int w);
};

template <class NeighbourhoodType>
class ArrayGraph : public Graph<int, 0x7fffffff> {
  public:
    class Iterator : public Graph<int, 0x7fffffff>::Iterator {
      private:
        NeighbourhoodType* ptr;
      public:
        Iterator(NeighbourhoodType* ptr) : Graph<int, 0x7fffffff>::Iterator(nullptr), ptr(ptr) {
          
        }
        bool operator!=(const Graph<int, 0x7fffffff>::Iterator& other) const {
          return ptr != ((Iterator&)other).ptr;
        }
        Neighbourhood<int, 0x7fffffff>& operator*() {
          return *ptr;
        }
        Graph<int, 0x7fffffff>::Iterator& operator++() {
          ptr++;
          return *this;
        }
    };
  private:
    int order_;
    NeighbourhoodType* data;
  public:
    ArrayGraph() : order_(0), data(new NeighbourhoodType[0]) {
      
    }
    ~ArrayGraph() {
      delete[] data;
    }
    Graph<int, 0x7fffffff>::Iterator begin() const {
      return Graph<int, 0x7fffffff>::Iterator(new Iterator(data));
    }
    Graph<int, 0x7fffffff>::Iterator end() const {
      return Graph<int, 0x7fffffff>::Iterator(new Iterator(data + order_));
    }
    Neighbourhood<int, 0x7fffffff>& operator[](int v) const {
      return data[v - 1];
    }
    int order() const {
      return order_;
    }
    void order(int new_order) {
      order_ = new_order;
      delete[] data;
      data = new NeighbourhoodType[order_];
      for (int i = 0; i < order_; i++) {
        data[i].vertex = i + 1;
      }
    }
};

template <> inline void ArrayGraph<ArrayNeighbourhood>::order(int new_order) {
  order_ = new_order;
  delete[] data;
  data = new ArrayNeighbourhood[order_];
  for (int i = 0; i < order_; i++) {
    data[i].vertex = i + 1;
    data[i].resize(order_);
  }
}

template <class NeighbourhoodType>
class MapGraph : public Graph<int, 0x7fffffff> {
  public:
    class Iterator : public Graph<int, 0x7fffffff>::Iterator {
      private:
        typename std::map<int, NeighbourhoodType>::const_iterator mapit;
      public:
        Iterator(
          typename std::map<int, NeighbourhoodType>::const_iterator mapit
        ) : Graph<int, 0x7fffffff>::Iterator(nullptr), mapit(mapit) {
          
        }
        bool operator!=(const Graph<int, 0x7fffffff>::Iterator& other) const {
          return mapit != ((Iterator&)other).mapit;
        }
        Neighbourhood<int, 0x7fffffff>& operator*() {
          return (Neighbourhood<int, 0x7fffffff>&)mapit->second;
        }
        Graph<int, 0x7fffffff>::Iterator& operator++() {
          mapit++;
          return *this;
        }
    };
  private:
    std::map<int, NeighbourhoodType> data;
  public:
    Graph<int, 0x7fffffff>::Iterator begin() const {
      return Graph<int, 0x7fffffff>::Iterator(new Iterator(data.begin()));
    }
    Graph<int, 0x7fffffff>::Iterator end() const {
      return Graph<int, 0x7fffffff>::Iterator(new Iterator(data.end()));
    }
    Neighbourhood<int, 0x7fffffff>& operator[](int v) const {
      return (Neighbourhood<int, 0x7fffffff>&)data.at(v);
    }
    int order() const {
      return data.size();
    }
    void order(int new_order) {
      data.clear();
      for (int u = 1; u <= new_order; u++) {
        data[u].vertex = u;
      }
    }
};

template <> inline void MapGraph<ArrayNeighbourhood>::order(int new_order) {
  data.clear();
  for (int u = 1; u <= new_order; u++) {
    data[u].vertex = u;
    data[u].resize(new_order);
  }
}

template <typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class AllPairsShortestPaths {
  private:
    int order;
    Weight** result;
    std::string funcname;
  public:
    AllPairsShortestPaths(
      const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G,
      std::function<void(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>&, Vertex, Weight*)> spfunc,
      const std::string& funcname
    );
    ~AllPairsShortestPaths();
    bool operator==(const AllPairsShortestPaths& other) const;
    bool operator!=(const AllPairsShortestPaths& other) const;
    void print(FILE* fp) const;
};

void scanUndirectedGraph(Graph<int, 0x7fffffff>& G, FILE* fp);
void scanDirectedGraph(Graph<int, 0x7fffffff>& G, FILE* fp);
void printDirectedGraph(const Graph<int, 0x7fffffff>& G, FILE* fp);

/**
 * Generates loop-free weighted undirected graphs without multiple edges, using
 * a uniform distribution.
 * G: container
 * N: number of vertices
 * max_weight: will generate weights in [1, maxWeight]
 */
void generateGraph(Graph<int, 0x7fffffff>& G, int N, int max_weight);

} // namespace graph

#include "Graph.inl.hpp"

#endif /* GRAPH_HPP_ */
