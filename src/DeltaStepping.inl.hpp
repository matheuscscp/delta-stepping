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

#include "ThreadManager.hpp"

#define DELTA DeltaStepping::delta<Weight>()

namespace graph {

template <typename Weight>
inline Weight DeltaStepping::delta() {
  return *((Weight*)delta_);
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
inline void SerialDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::relax(const Vertex& v, Weight x) {
  DeltaStepping::incRelaxations();
  Weight& tent_v = tent[v];
  if (x < tent_v) {
    Size floor_tent_v_delta = Size(floor(double(tent_v)/DELTA));
    if (floor_tent_v_delta < B.size()) {
      B[floor_tent_v_delta].remove(v);
    }
    Size floor_x_delta = Size(floor(double(x)/DELTA));
    if (floor_x_delta >= B.size()) {
      B.insert(B.end(), floor_x_delta + 1 - B.size(), std::list<Vertex>());
    }
    B[floor_x_delta].push_back(v);
    tent_v = x;
  }
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
void SerialDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist) {
  std::list<Vertex>* heavy = new std::list<Vertex>[G.order() + 1];
  std::list<Vertex>* light = new std::list<Vertex>[G.order() + 1];
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
  relax(source, IDENTITY);
  for (Size i = 0; i < B.size(); i++) {
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
  delete[] heavy;
  delete[] light;
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
inline void ParallelDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::relax(const Vertex& v, Weight x) {
  DeltaStepping::incRelaxations();
  Weight& tent_v = tent[v];
  if (x < tent_v) {
    Size floor_tent_v_delta = Size(floor(double(tent_v)/DELTA));
    if (floor_tent_v_delta < B.size()) {
      B[floor_tent_v_delta].remove(v);
    }
    Size floor_x_delta = Size(floor(double(x)/DELTA));
    if (floor_x_delta >= B.size()) {
      B.insert(B.end(), floor_x_delta + 1 - B.size(), std::list<Vertex>());
    }
    B[floor_x_delta].push_back(v);
    tent_v = x;
  }
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
void ParallelDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist) {
  std::list<Vertex>* heavy = new std::list<Vertex>[G.order() + 1];
  std::list<Vertex>* light = new std::list<Vertex>[G.order() + 1];
  B.clear();
  tent = dist;
  {
    JobPool jobs;
    for (int tid = 0, nth = ThreadManager::nthreads(); tid < nth; tid++) {
      jobs.dispatch([&G, tid, nth, heavy, light, this]() {
        Size V = G.order(), Vpernth = V/nth, rem = V%nth;
        Vertex first = tid*Vpernth + 1, last = (tid + 1)*Vpernth;
        if (rem != 0) {
          Size W = Vpernth + 1;
          if (tid < rem) {
            first = tid*W + 1;
            last = (tid + 1)*W;
          }
          else {
            first = rem*W + (tid - rem)*Vpernth + 1;
            last = rem*W + (tid + 1 - rem)*Vpernth;
          }
        }
        for (Vertex u = first; u <= last; u++) {
          auto& v = G[u];
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
      });
    }
  }
  relax(source, IDENTITY);
  Size i = 0;
  while (i < B.size()) { // while there are buckets to be processed
    std::list<Vertex> S;
    while (B[i].size() > 0) { // process current bucket
      std::list<std::pair<Vertex, Weight>> Req;
      auto& B_i = B[i];
      for (auto& v : B_i) { // enqueue current vertex neighbours
        Weight tent_v = tent[v];
        auto& light_v = light[v];
        for (auto& w : light_v) { // vertex light neighbours
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
    i++;
  }
  delete[] heavy;
  delete[] light;
}

} // namespace graph

#endif /* DELTASTEPPING_INL_HPP_ */
