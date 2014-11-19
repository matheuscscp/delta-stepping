/*
 * DeltaStepping.inl.hpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#ifndef DELTASTEPPING_INL_HPP_
#define DELTASTEPPING_INL_HPP_

#include <vector>
#include <cmath>

#define DELTA DeltaStepping::delta<Weight>()

namespace graph {

template <typename Weight>
inline Weight DeltaStepping::delta() {
  return *((Weight*)delta_);
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
void SerialDeltaStepping<Weight, INFINITE, Vertex, nullvertex, Size>::relax(const Vertex& v, Weight x) {
  DeltaStepping::incRelaxations();
  Weight& tent_v = tent[v];
  if (x < tent_v) {
    size_t floor_tent_v_delta = size_t(floor(double(tent_v)/DELTA));
    if (floor_tent_v_delta < B.size()) {
      B[floor_tent_v_delta].remove(v);
    }
    size_t floor_x_delta = size_t(floor(double(x)/DELTA));
    if (floor_x_delta >= B.size()) {
      B.insert(B.end(), floor_x_delta + 1 - B.size(), std::list<Vertex>());
    }
    B[floor_x_delta].push_back(v);
    tent_v = x;
  }
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
void SerialDeltaStepping<Weight, INFINITE, Vertex, nullvertex, Size>::run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist) {
  heavy.clear();
  light.clear();
  B.clear();
  tent = dist;
  for (auto& v : G) {
    std::list<Vertex>& h = heavy[v.vertex];
    std::list<Vertex>& l = light[v.vertex];
    for (auto w : v) {
      if (w.weight > DELTA) {
        h.push_back(w.vertex);
      }
      else {
        l.push_back(w.vertex);
      }
    }
    tent[v.vertex] = INFINITE;
  }
  relax(source, 0);
  size_t i;
  for (i = 0; i < B.size(); i++) {
    std::list<Vertex> S;
    while (B[i].size() > 0) {
      std::list<std::pair<Vertex, Weight>> Req;
      auto& B_i = B[i];
      for (auto& v : B_i) {
        Weight tent_v = tent[v];
        auto& light_v = light[v];
        for (auto& w : light_v) {
          Req.emplace_back(w, tent_v + G[v][w].weight);
        }
        S.push_back(v);
      }
      B[i].clear();
      for (auto& v_x : Req) {
        relax(v_x.first, v_x.second);
      }
    }
    std::list<std::pair<Vertex, Weight>> Req;
    for (auto& v : S) {
      Weight tent_v = tent[v];
      auto& heavy_v = heavy[v];
      for (auto& w : heavy_v) {
        Req.emplace_back(w, tent_v + G[v][w].weight);
      }
    }
    for (auto& v_x : Req) {
      relax(v_x.first, v_x.second);
    }
  }
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
std::string SerialDeltaStepping<Weight, INFINITE, Vertex, nullvertex, Size>::name() const {
  return "Serial Delta Stepping";
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
void ParallelDeltaStepping<Weight, INFINITE, Vertex, nullvertex, Size>::run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist) {
  //TODO
}

template <typename Weight, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
std::string ParallelDeltaStepping<Weight, INFINITE, Vertex, nullvertex, Size>::name() const {
  return "Parallel Delta Stepping";
}

} // namespace graph

#endif /* DELTASTEPPING_INL_HPP_ */
