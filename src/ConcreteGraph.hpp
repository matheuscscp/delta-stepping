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

} // namespace graph

#endif /* CONCRETEGRAPH_HPP_ */
