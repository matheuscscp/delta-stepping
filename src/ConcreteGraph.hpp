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
  private:
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

template <class NeighbourhoodType, typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class MapGraph : public Graph<Weight, INFINITE, Vertex, nullvertex, Size> {
  public:
    class Iterator : public Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator {
      private:
        typename std::map<Vertex, NeighbourhoodType>::const_iterator mapit;
      public:
        Iterator(typename std::map<Vertex, NeighbourhoodType>::const_iterator mapit);
        bool operator!=(const typename Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& other) const;
        Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>& operator*();
        typename Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator& operator++();
    };
  private:
    std::map<Vertex, NeighbourhoodType> data;
  public:
    typename Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator begin() const;
    typename Graph<Weight, INFINITE, Vertex, nullvertex, Size>::Iterator end() const;
    Neighbourhood<Weight, INFINITE, Vertex, nullvertex, Size>& operator[](Vertex v) const;
    Size order() const;
    void order(Size new_order);
};

typedef ArrayNeighbourhood<int, 0x7fffffff>                 IntArrayNeighbourhood;
typedef MapNeighbourhood<int, 0x7fffffff>                   IntMapNeighbourhood;
typedef ArrayGraph<IntArrayNeighbourhood, int, 0x7fffffff>  IntArrayGraphArrayNeighbourHood;
typedef ArrayGraph<IntMapNeighbourhood, int, 0x7fffffff>    IntArrayGraphMapNeighbourHood;
typedef MapGraph<IntArrayNeighbourhood, int, 0x7fffffff>    IntMapGraphArrayNeighbourHood;
typedef MapGraph<IntMapNeighbourhood, int, 0x7fffffff>      IntMapGraphMapNeighbourHood;

} // namespace graph

#include "ConcreteGraph.inl.hpp"

#endif /* CONCRETEGRAPH_HPP_ */
