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
#include <map>
#include <cstdio>

namespace graph {

template <class VertexType, typename Weight>
class GenericEdge {
  public:
    VertexType source, target;
    Weight weight;
    GenericEdge(VertexType source, VertexType target, Weight weight);
};

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
    
    template <class VertexType>
    static void build(Graph& G, const std::set<VertexType>& vertices, const std::set<GenericEdge<VertexType, Weight>>& edges);
};

typedef Edge<int, 0x7fffffff>           IntEdge;
typedef Neighbourhood<int, 0x7fffffff>  IntNeighbourhood;
typedef Graph<int, 0x7fffffff>          IntGraph;

} // namespace graph

#include "Graph.inl.hpp"

#endif /* GRAPH_HPP_ */
