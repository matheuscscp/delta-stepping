/*
 * ConcreteGraph.hpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#ifndef CONCRETEGRAPH_HPP_
#define CONCRETEGRAPH_HPP_

#include "Graph.hpp"

namespace graph {

template <typename Weight, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class ArrayNeighbourhood : public Neighbourhood<Weight, Vertex, nullvertex, Size> {
  public:
    class Iterator : public Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator {
      private:
        Edge<Weight, Vertex, nullvertex>* ptr;
      public:
        Iterator(Edge<Weight, Vertex, nullvertex>* ptr);
        bool operator!=(const typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator& other) const;
        Edge<Weight, Vertex, nullvertex> operator*();
        typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator& operator++();
    };
  private:
    Size size_;
    Edge<Weight, Vertex, nullvertex>* data;
    Size degree_;
  public:
    ArrayNeighbourhood();
    ~ArrayNeighbourhood();
    typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator begin() const;
    typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator end() const;
    Edge<Weight, Vertex, nullvertex> operator[](Vertex v) const;
    Size degree() const;
    void resize(Size new_size);
    void edge(Vertex v, Weight w);
};

template <typename Weight, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class MapNeighbourhood : public Neighbourhood<Weight, Vertex, nullvertex, Size> {
  public:
    class Iterator : public Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator {
      private:
        typename std::map<Vertex, Edge<Weight, Vertex, nullvertex>>::const_iterator mapit;
      public:
        Iterator(typename std::map<Vertex, Edge<Weight, Vertex, nullvertex>>::const_iterator mapit);
        bool operator!=(const typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator& other) const;
        Edge<Weight, Vertex, nullvertex> operator*();
        typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator& operator++();
    };
  private:
    std::map<Vertex, Edge<Weight, Vertex, nullvertex>> data;
  public:
    typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator begin() const;
    typename Neighbourhood<Weight, Vertex, nullvertex, Size>::Iterator end() const;
    Edge<Weight, Vertex, nullvertex> operator[](Vertex v) const;
    Size degree() const;
    void resize(Size new_size);
    void edge(Vertex v, Weight w);
};

template <class NeighbourhoodType, typename Weight, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class ArrayGraph : public Graph<Weight, Vertex, nullvertex, Size> {
  public:
    class Iterator : public Graph<Weight, Vertex, nullvertex, Size>::Iterator {
      private:
        NeighbourhoodType* ptr;
      public:
        Iterator(NeighbourhoodType* ptr);
        bool operator!=(const typename Graph<Weight, Vertex, nullvertex, Size>::Iterator& other) const;
        Neighbourhood<Weight, Vertex, nullvertex, Size>& operator*();
        typename Graph<Weight, Vertex, nullvertex, Size>::Iterator& operator++();
    };
  private:
    Size order_;
    NeighbourhoodType* data;
  public:
    ArrayGraph();
    ~ArrayGraph();
    typename Graph<Weight, Vertex, nullvertex, Size>::Iterator begin() const;
    typename Graph<Weight, Vertex, nullvertex, Size>::Iterator end() const;
    Neighbourhood<Weight, Vertex, nullvertex, Size>& operator[](Vertex v) const;
    Size order() const;
    void order(Size new_order);
};

template <class NeighbourhoodType, typename Weight, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class MapGraph : public Graph<Weight, Vertex, nullvertex, Size> {
  public:
    class Iterator : public Graph<Weight, Vertex, nullvertex, Size>::Iterator {
      private:
        typename std::map<Vertex, NeighbourhoodType>::const_iterator mapit;
      public:
        Iterator(typename std::map<Vertex, NeighbourhoodType>::const_iterator mapit);
        bool operator!=(const typename Graph<Weight, Vertex, nullvertex, Size>::Iterator& other) const;
        Neighbourhood<Weight, Vertex, nullvertex, Size>& operator*();
        typename Graph<Weight, Vertex, nullvertex, Size>::Iterator& operator++();
    };
  private:
    std::map<Vertex, NeighbourhoodType> data;
  public:
    typename Graph<Weight, Vertex, nullvertex, Size>::Iterator begin() const;
    typename Graph<Weight, Vertex, nullvertex, Size>::Iterator end() const;
    Neighbourhood<Weight, Vertex, nullvertex, Size>& operator[](Vertex v) const;
    Size order() const;
    void order(Size new_order);
};

typedef ArrayNeighbourhood<int>                   IntArrayNeighbourhood;
typedef MapNeighbourhood<int>                     IntMapNeighbourhood;
typedef ArrayGraph<IntArrayNeighbourhood, int>    IntArrayGraphArrayNeighbourhood;
typedef ArrayGraph<IntMapNeighbourhood, int>      IntArrayGraphMapNeighbourhood;
typedef MapGraph<IntArrayNeighbourhood, int>      IntMapGraphArrayNeighbourhood;
typedef MapGraph<IntMapNeighbourhood, int>        IntMapGraphMapNeighbourhood;
typedef MapNeighbourhood<float>                   FloatMapNeighbourhood;
typedef ArrayGraph<FloatMapNeighbourhood, float>  FloatArrayGraphMapNeighbourhood;

} // namespace graph

#include "ConcreteGraph.inl.hpp"

#endif /* CONCRETEGRAPH_HPP_ */
