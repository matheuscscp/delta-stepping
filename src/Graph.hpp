/*
 * Graph.hpp
 *
 *  Created on: Nov 4, 2014
 *      Author: Pimenta
 */

#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <memory>
#include <set>

namespace graph {

template <class VertexType, typename Weight>
class GenericEdge {
  public:
    VertexType source, target;
    Weight weight;
    GenericEdge(VertexType source, VertexType target, Weight weight);
};

template <typename Weight, typename Vertex = int, Vertex nullvertex = 0>
class Edge {
  public:
    Vertex vertex;
    Weight weight;
    Edge(Vertex vertex = nullvertex, Weight weight = Weight(0x7fffffff));
    bool operator<(const Edge& other) const;
};

template <typename Weight, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class Neighbourhood {
  public:
    class Iterator : public std::iterator<std::forward_iterator_tag, Edge<Weight, Vertex, nullvertex>> {
      private:
        std::shared_ptr<Iterator> it, itend;
      public:
        Iterator(Iterator* it, Iterator* itend);
        virtual ~Iterator();
        virtual bool operator!=(const Iterator& other) const;
        virtual Edge<Weight, Vertex, nullvertex> operator*();
        virtual Iterator& operator++();
    };
    Vertex vertex;
    Neighbourhood(Vertex vertex = nullvertex);
    virtual ~Neighbourhood();
    virtual Iterator begin() const = 0;
    virtual Iterator end() const = 0;
    virtual Edge<Weight, Vertex, nullvertex> operator[](Vertex v) const = 0;
    virtual Size degree() const = 0;
    virtual void resize(Size new_size) = 0;
    virtual void edge(Vertex v, Weight w) = 0;
};

template <typename Weight, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class Graph {
  public:
    class Iterator : public std::iterator<std::forward_iterator_tag, Neighbourhood<Weight, Vertex, nullvertex, Size>> {
      private:
        std::shared_ptr<Iterator> it;
      public:
        Iterator(Iterator* it);
        virtual ~Iterator();
        virtual bool operator!=(const Iterator& other) const;
        virtual Neighbourhood<Weight, Vertex, nullvertex, Size>& operator*();
        virtual Iterator& operator++();
    };
  private:
    Weight maxweight_;
    Size maxdegree_;
  public:
    Graph();
    virtual ~Graph();
    virtual Iterator begin() const = 0;
    virtual Iterator end() const = 0;
    virtual Neighbourhood<Weight, Vertex, nullvertex, Size>& operator[](Vertex v) const = 0;
    virtual Size order() const = 0;
    virtual void order(Size new_order) = 0;
    virtual Weight maxweight() const;
    virtual Size maxdegree() const;
    virtual void updatemax();
    
    template <class VertexType>
    static void build(Graph& G, const std::set<VertexType>& vertices, const std::set<GenericEdge<VertexType, Weight>>& edges);
};

typedef Edge<int>             IntEdge;
typedef Neighbourhood<int>    IntNeighbourhood;
typedef Graph<int>            IntGraph;
typedef Edge<float>           FloatEdge;
typedef Neighbourhood<float>  FloatNeighbourhood;
typedef Graph<float>          FloatGraph;

} // namespace graph

#include "Graph.inl.hpp"

#endif /* GRAPH_HPP_ */
