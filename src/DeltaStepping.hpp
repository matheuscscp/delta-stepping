/*
 * DeltaStepping.hpp
 *
 *  Created on: Nov 5, 2014
 *      Author: Pimenta
 */

#ifndef DELTASTEPPING_HPP_
#define DELTASTEPPING_HPP_

#include "SSSPAlgorithm.hpp"

namespace graph {

template <typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class SerialDeltaStepping : public SSSPAlgorithm<Weight, INFINITE, Vertex, nullvertex, Size> {
  public:
    void run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist) const;
    std::string name() const;
};

template <typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class ParallelDeltaStepping : public SSSPAlgorithm<Weight, INFINITE, Vertex, nullvertex, Size> {
  public:
    void run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist) const;
    std::string name() const;
};

} // namespace graph

#include "DeltaStepping.inl.hpp"

#endif /* DELTASTEPPING_HPP_ */
