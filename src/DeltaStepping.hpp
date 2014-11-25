/*
 * DeltaStepping.hpp
 *
 *  Created on: Nov 5, 2014
 *      Author: Pimenta
 */

#ifndef DELTASTEPPING_HPP_
#define DELTASTEPPING_HPP_

#include <atomic>

#include "SSSPAlgorithm.hpp"
#include "Bucket.hpp"

namespace graph {

template <typename Weight, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class SerialDeltaStepping : public SSSPAlgorithm<Weight, Vertex, nullvertex, Size> {
  private:
    // local
    Weight delta;
    BucketArray<Vertex, Size> B;
    // out
    Weight* tent;
    uint64_t relaxations_;
  public:
    SerialDeltaStepping();
    void run(const Graph<Weight, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist);
    uint64_t relaxations() const;
  private:
    inline void findRequests(const Graph<Weight, Vertex, nullvertex, Size>& G, Vertex w, std::list<Vertex>* kind, std::list<std::pair<Vertex, Weight>>& Req);
    inline void relaxRequests(std::list<std::pair<Vertex, Weight>>& Req);
    inline void relax(Vertex w, Weight x);
};

template <typename Weight, typename Vertex = int, Vertex nullvertex = 0, typename Size = int>
class ParallelDeltaStepping : public SSSPAlgorithm<Weight, Vertex, nullvertex, Size> {
  private:
    // in
    Size threshold;
    // local
    Weight delta;
    BucketArray<Vertex, Size> B;
    // out
    Weight* tent;
    std::atomic<uint64_t> relaxations_;
  public:
    ParallelDeltaStepping(Size threshold, Weight delta);
    ~ParallelDeltaStepping();
    void run(const Graph<Weight, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist);
    uint64_t relaxations() const;
  private:
    inline void findRequests(const Graph<Weight, Vertex, nullvertex, Size>& G, Vertex w, std::list<Vertex>* kind, std::list<std::pair<Vertex, Weight>>& Req);
    inline void relaxRequests(std::list<std::pair<Vertex, Weight>>& Req);
    inline void relaxRequestsLocal(BucketArray<Vertex, Size>& tB, std::list<std::pair<Vertex, Weight>>& Req);
    inline void relax(Vertex w, Weight x);
    inline void relaxLocal(BucketArray<Vertex, Size>& tB, Vertex w, Weight x);
};

} // namespace graph

#include "DeltaStepping.inl.hpp"

#endif /* DELTASTEPPING_HPP_ */
