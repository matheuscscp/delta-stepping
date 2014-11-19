/*
 * AllPairsShortestPaths.hpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#ifndef ALLPAIRSSHORTESTPATHS_HPP_
#define ALLPAIRSSHORTESTPATHS_HPP_

#include "SSSPAlgorithm.hpp"

namespace graph {

template <typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class AllPairsShortestPaths {
  private:
    int order;
    Weight** result;
  public:
    AllPairsShortestPaths(
      const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G,
      const SSSPAlgorithm<Weight, INFINITE, Vertex, nullvertex, Size>& ssspfunc
    );
    ~AllPairsShortestPaths();
    bool operator==(const AllPairsShortestPaths& other) const;
    bool operator!=(const AllPairsShortestPaths& other) const;
};

} // namespace graph

#include "AllPairsShortestPaths.inl.hpp"

#endif /* ALLPAIRSSHORTESTPATHS_HPP_ */
