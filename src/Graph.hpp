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
    Data* res;
  public:
    AllPairsShortestPaths(
      const Graph& G,
      std::function<Weight*(const Graph&, Vertex)> spfunc
    ) : N(G.size()), res(new Data) {
      for (auto& kv : G) {
        Weight* shortest_path_tree = spfunc(G, kv.first);
        for (auto& kv2 : G) {
          res->data[kv.first][kv2.first] = shortest_path_tree[kv2.first];
        }
        delete[] shortest_path_tree;
      }
    }
    
    ~AllPairsShortestPaths() {
      delete res;
    }
    
    bool operator==(const AllPairsShortestPaths& other) {
      if (N != other.N) {
        return false;
      }
      
      for (Vertex source = 1; source <= N; source++) {
        for (Vertex target = 1; target <= N; target++) {
          if (res->data[source][target] != other.res->data[source][target]) {
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
      
      for (Vertex source = 1; source <= N; source++) {
        for (Vertex target = 1; target <= N; target++) {
          if (res->data[source][target] != other.res->data[source][target]) {
            return true;
          }
        }
      }
      
      return false;
    }
    
    void print(FILE* fp, const char* funcname) {
      fprintf(fp, "%s:\n", funcname);
      for (Vertex source = 1; source <= N; source++) {
        for (Vertex target = 1; target <= N; target++) {
          Weight w = res->data[source][target];
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
