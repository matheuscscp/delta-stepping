/*
 * AllPairsShortestPaths.hpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#ifndef ALLPAIRSSHORTESTPATHS_HPP_
#define ALLPAIRSSHORTESTPATHS_HPP_

#include <functional>
#include <string>
#include <cstdio>

#include "Graph.hpp"

namespace graph {

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

} // namespace graph

#include "AllPairsShortestPaths.inl.hpp"

#endif /* ALLPAIRSSHORTESTPATHS_HPP_ */