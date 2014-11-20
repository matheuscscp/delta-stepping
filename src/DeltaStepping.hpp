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

class DeltaStepping {
  private:
    static void* delta_;
    static uint64_t relaxations_;
  public:
    static void init(void* delta);
    static void close();
    template <typename Weight>
    static inline Weight delta();
    static void incRelaxations();
    static uint64_t relaxations();
};

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class SerialDeltaStepping : public SSSPAlgorithm<Weight, INFINITE, Vertex, nullvertex, Size> {
  private:
    // local
    std::vector<std::list<Vertex>> B;
    // out
    Weight* tent; // tentative distance. equals distance after the algorithm
    inline void relax(const Vertex& v, Weight x);
  public:
    void run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist);
};

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class ParallelDeltaStepping : public SSSPAlgorithm<Weight, INFINITE, Vertex, nullvertex, Size> {
  private:
    // local
    std::vector<std::list<Vertex>> B;
    // out
    Weight* tent; // tentative distance. equals distance after the algorithm
    inline void relax(const Vertex& v, Weight x);
  public:
    void run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist);
};

} // namespace graph

#include "DeltaStepping.inl.hpp"

#endif /* DELTASTEPPING_HPP_ */
