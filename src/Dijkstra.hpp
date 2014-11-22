/*
 * Dijkstra.hpp
 *
 *  Created on: Nov 5, 2014
 *      Author: Pimenta
 */

#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_

#include "SSSPAlgorithm.hpp"

namespace graph {

template <typename Weight, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class SerialDijkstra : public SSSPAlgorithm<Weight, Vertex, nullvertex, Size> {
  public:
    void run(const Graph<Weight, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist);
};

} // namespace graph

#include "Dijkstra.inl.hpp"

#endif /* DIJKSTRA_HPP_ */
