/*
 * ConcreteGraph.hpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#ifndef CONCRETEGRAPH_HPP_
#define CONCRETEGRAPH_HPP_

#include <map>

#include "Graph.hpp"

namespace graph {

template <typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class ArrayNeighbourhood : public Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size> {
  public:
    class Iterator : public Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator {
      private:
        Edge<Weight, INFINITE, Vertex, nullvertex>* ptr;
      public:
        Iterator(Edge<Weight, INFINITE, Vertex, nullvertex>* ptr);
        bool operator!=(const typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& other) const;
        Edge<Weight, INFINITE, Vertex, nullvertex> operator*();
        typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& operator++();
    };
  private:
    Size size_;
    Edge<Weight, INFINITE, Vertex, nullvertex>* data;
    Size degree_;
  public:
    ArrayNeighbourhood();
    ~ArrayNeighbourhood();
    typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator begin() const;
    typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator end() const;
    Edge<Weight, INFINITE, Vertex, nullvertex> operator[](Vertex v) const;
    Size degree() const;
    void resize(Size new_size);
    void edge(Vertex v, Vertex w);
};

template <typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class MapNeighbourhood : public Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size> {
  public:
    class Iterator : public Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator {
      private:
        typename std::map<Vertex, Edge<Weight, INFINITE, Vertex, nullvertex>>::const_iterator mapit;
      public:
        Iterator(typename std::map<Vertex, Edge<Weight, INFINITE, Vertex, nullvertex>>::const_iterator mapit);
        bool operator!=(const typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& other) const;
        Edge<Weight, INFINITE, Vertex, nullvertex> operator*();
        typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& operator++();
    };
  private:
    std::map<Vertex, Edge<Weight, INFINITE, Vertex, nullvertex>> data;
  public:
    typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator begin() const;
    typename Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator end() const;
    Edge<Weight, INFINITE, Vertex, nullvertex> operator[](Vertex v) const;
    Size degree() const;
    void resize(Size new_size);
    void edge(Vertex v, Vertex w);
};

template <class NeighbourhoodType, typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class ArrayGraph : public Graph<Weight, INFINITE, Vertex, nullvertex, Size> {
  public:
    class Iterator : public Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator {
      private:
        NeighbourhoodType* ptr;
      public:
        Iterator(NeighbourhoodType* ptr);
        bool operator!=(const typename Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& other) const;
        Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>& operator*();
        typename Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& operator++();
    };
  public:
    Size order_;
    NeighbourhoodType* data;
  public:
    ArrayGraph();
    ~ArrayGraph();
    typename Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator begin() const;
    typename Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator end() const;
    Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>& operator[](Vertex v) const;
    Size order() const;
    void order(Size new_order);
};

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
        data[u].resize(new_order);
      }
    }
};

typedef ArrayNeighbourhood<int, 0x7fffffff>                 IntArrayNeighbourhood;
typedef MapNeighbourhood<int, 0x7fffffff>                   IntMapNeighbourhood;
typedef ArrayGraph<IntArrayNeighbourhood, int, 0x7fffffff>  IntArrayGraphArrayNeighbourHood;
typedef ArrayGraph<IntMapNeighbourhood, int, 0x7fffffff>    IntArrayGraphMapNeighbourHood;
//TODO

} // namespace graph

#include "ConcreteGraph.inl.hpp"

#endif /* CONCRETEGRAPH_HPP_ */
