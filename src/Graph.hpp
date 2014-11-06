/*
 * Graph.hpp
 *
 *  Created on: Nov 4, 2014
 *      Author: Pimenta
 */

#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <cstdio>
#include <map>
#include <functional>

#define INF 0x7FFFFFFF

typedef int Vertex;
typedef int Weight;
typedef std::map<Vertex, std::map<Vertex, Weight>> Graph;

template <int maxN>
class AllPairsShortestPaths {
  private:
    struct Data {
      Weight data[maxN][maxN];
    };
    
    int N;
    Data* result;
  public:
    AllPairsShortestPaths(
      const Graph& G,
      std::function<Weight(const Graph&, Vertex, Vertex)> spfunc
    ) : N(G.size()), result(new Data) {
      for (auto& kv : G) {
        for (auto& kv2 : G) {
          result->data[kv.first][kv2.first] = spfunc(G, kv.first, kv2.first);
        }
      }
    }
    
    ~AllPairsShortestPaths() {
      delete result;
    }
    
    bool operator==(const AllPairsShortestPaths& other) {
      if (N != other.N) {
        return false;
      }
      
      for (Vertex s = 1; s <= N; s++) {
        for (Vertex d = 1; d <= N; d++) {
          if (result->data[s][d] != other.result->data[s][d]) {
            return false;
          }
        }
      }
      
      return true;
    }
    
    bool operator!=(const AllPairsShortestPaths& other) {
      if (N != other.N) {
        return true;
      }
      
      for (Vertex s = 1; s <= N; s++) {
        for (Vertex d = 1; d <= N; d++) {
          if (result[s][d] != other.result[s][d]) {
            return true;
          }
        }
      }
      
      return false;
    }
    
    void print(FILE* fp, const char* funcname) {
      fprintf(fp, "%s:\n", funcname);
      for (Vertex s = 1; s <= N; s++) {
        for (Vertex d = 1; d <= N; d++) {
          Weight w = result->data[s][d];
          if (w == INF) {
            fprintf(fp, "  inf ");
          }
          else {
            fprintf(fp, "%5d ", w);
          }
        }
        fprintf(fp, "\n");
      }
    }
};

Graph scanUndirectedGraph(FILE* fp);
Graph scanDirectedGraph(FILE* fp);
void printDirectedGraph(FILE* fp, const Graph& G);

/**
 * Generates loop-free weighted undirected graphs without multiple edges, using
 * a uniform distribution.
 * N: number of vertices
 * maxWeight: will generate weights in [1, maxWeight]
 */
Graph generateGraph(int N, Weight maxWeight);

#endif /* GRAPH_HPP_ */
