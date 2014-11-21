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
#include "Bucket.hpp"

namespace graph {

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class SerialDeltaStepping : public SSSPAlgorithm<Weight, INFINITE, Vertex, nullvertex, Size> {
  private:
    // in
    Weight delta;
    // local
    BucketArray<Vertex, Size> B;
    // out
    Weight* tent;
    uint64_t relaxations_;
  public:
    SerialDeltaStepping(Weight delta);
    void run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist);
    uint64_t relaxations() const;
  private:
    inline void findRequests(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex w, std::list<Vertex>* kind, std::list<std::pair<Vertex, Weight>>& Req);
    inline void relaxRequests(std::list<std::pair<Vertex, Weight>>& Req);
    inline void relax(Vertex w, Weight x);
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
    inline void relax(Vertex v, Weight x);
};

} // namespace graph

#include "DeltaStepping.inl.hpp"

#endif /* DELTASTEPPING_HPP_ */
