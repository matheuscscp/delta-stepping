/*
 * DeltaStepping.hpp
 *
 *  Created on: Nov 5, 2014
 *      Author: Pimenta
 */

#ifndef DELTASTEPPING_HPP_
#define DELTASTEPPING_HPP_

#include <list>
#include <vector>

#include "SSSPAlgorithm.hpp"

namespace graph {

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class SerialDeltaStepping : public SSSPAlgorithm<Weight, INFINITE, Vertex, nullvertex, Size> {
  private:
    // in
    Weight delta;
    // local
    std::vector<std::list<Vertex>> B;
    // out
    Weight* tent;
    uint64_t relaxations_;
  public:
    SerialDeltaStepping(Weight delta);
    void run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist);
    uint64_t relaxations() const;
  private:
    inline void relax(const Vertex& v, Weight x);
};

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class ParallelDeltaStepping : public SSSPAlgorithm<Weight, INFINITE, Vertex, nullvertex, Size> {
  private:
    // in
    Weight delta;
    // local
    std::vector<std::list<Vertex>> B;
    pthread_mutex_t relax_mutex;
    // out
    Weight* tent;
    uint64_t relaxations_;
  public:
    ParallelDeltaStepping(Weight delta);
    ~ParallelDeltaStepping();
    void run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist);
    uint64_t relaxations() const;
  private:
    inline void relax(const Vertex& v, Weight x);
};

} // namespace graph

#include "DeltaStepping.inl.hpp"

#endif /* DELTASTEPPING_HPP_ */
