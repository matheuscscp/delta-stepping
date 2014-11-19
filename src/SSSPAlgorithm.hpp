/*
 * SSSPAlgorithm.hpp
 *
 *  Created on: Nov 19, 2014
 *      Author: Pimenta
 */

#ifndef SSSPALGORITHM_HPP_
#define SSSPALGORITHM_HPP_

#include "Graph.hpp"

namespace graph {

template <typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class SSSPAlgorithm {
  public:
    virtual ~SSSPAlgorithm();
    virtual void clear() = 0;
    virtual void run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>&, Vertex, Weight*) = 0;
    virtual std::string name() const = 0;
};

} // namespace graph

#include "SSSPAlgorithm.inl.hpp"

#endif /* SSSPALGORITHM_HPP_ */
