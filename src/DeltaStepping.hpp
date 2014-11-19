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
  public:
    template <typename Weight>
    static inline Weight delta();
    static void delta(void* new_delta);
};

template <typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class SerialDeltaStepping : public SSSPAlgorithm<Weight, INFINITE, Vertex, nullvertex, Size> {
  private:
    // local
    std::map<Vertex, std::list<Vertex>> heavy, light;
    std::vector<std::list<Vertex>> B;
    // out
    Weight* tent; // tentative distance. equals distance after the algorithm
    void relax(const Vertex& v, Weight x);
  public:
    void clear();
    void run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist);
    std::string name() const;
};

template <typename Weight, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class ParallelDeltaStepping : public SSSPAlgorithm<Weight, INFINITE, Vertex, nullvertex, Size> {
  public:
    void clear();
    void run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist);
    std::string name() const;
};

} // namespace graph

#include "DeltaStepping.inl.hpp"

#endif /* DELTASTEPPING_HPP_ */
