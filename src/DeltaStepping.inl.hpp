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

namespace graph {

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
SerialDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::SerialDeltaStepping(Weight delta) : delta(delta), tent(nullptr), relaxations_(0) {
  
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
void SerialDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist) {
  std::list<Vertex>* heavy = new std::list<Vertex>[G.order() + 1];
  std::list<Vertex>* light = new std::list<Vertex>[G.order() + 1];
  B.init(Size(ceil(double(G.maxweight())/delta))*3 + 1);//FIXME
  tent = dist;
  for (auto& v : G) {
    std::list<Vertex>& h = heavy[v.vertex];
    std::list<Vertex>& l = light[v.vertex];
    for (auto w : v) {
      if (w.weight > delta) {
        h.push_back(w.vertex);
      }
      else {
        l.push_back(w.vertex);
      }
    }
    tent[v.vertex] = INFINITE;
  }
  relax(source, IDENTITY);
  Size i = 0;
  while (!B.empty()) {
    i = B.firstnonempty(i);
    std::list<Vertex> R;
    while (B.size(i) > 0) {
      std::list<std::pair<Vertex, Weight>> Req;
      while (B.size(i) > 0) {
        Vertex v = B.remove(i);
        findRequests(G, v, light, Req);
        R.push_back(v);
      }
      relaxRequests(Req);
    }
    std::list<std::pair<Vertex, Weight>> Req;
    for (auto v = R.begin(); v != R.end();) {
      findRequests(G, *v, heavy, Req);
      R.erase(v++);
    }
    relaxRequests(Req);
  }
  delete[] heavy;
  delete[] light;
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
uint64_t SerialDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::relaxations() const {
  return relaxations_;
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
inline void SerialDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::findRequests(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex w, std::list<Vertex>* kind, std::list<std::pair<Vertex, Weight>>& Req) {
  Weight tent_w = tent[w];
  std::list<Vertex>& kind_w = kind[w];
  for (Vertex v : kind_w) {
    Req.emplace_back(v, tent_w + G[w][v].weight);
  }
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
inline void SerialDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::relaxRequests(std::list<std::pair<Vertex, Weight>>& Req) {
  for (auto it = Req.begin(); it != Req.end();) {
    relax(it->first, it->second);
    Req.erase(it++);
  }
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
inline void SerialDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::relax(Vertex w, Weight x) {
  relaxations_++;
  Weight& tent_w = tent[w];
  if (x < tent_w) {
    if (tent_w < INFINITE) {
      B.remove(Size(floor(double(tent_w)/delta)), w);
    }
    B.insert(Size(floor(double(x)/delta)), w);
    tent_w = x;
  }
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
ParallelDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::ParallelDeltaStepping(Weight delta) : delta(delta), tent(nullptr), relaxations_(0) {
  pthread_mutex_init(&relax_mutex, nullptr);
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
ParallelDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::~ParallelDeltaStepping() {
  pthread_mutex_destroy(&relax_mutex);
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
void ParallelDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::run(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist) {
  std::list<Vertex>* heavy = new std::list<Vertex>[G.order() + 1];
  std::list<Vertex>* light = new std::list<Vertex>[G.order() + 1];
  B.init(Size(ceil(double(G.maxweight())/delta))*3 + 1);//FIXME
  tent = dist;
  // parallel initialization
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
            if (w.weight > delta) {
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
  while (!B.empty()) {
    i = B.firstnonempty(i);
    std::list<Vertex> R;
    while (B.size(i) > 0) {
      std::list<std::pair<Vertex, Weight>> Req;
      while (B.size(i) > 0) {
        Vertex v = B.remove(i);
        findRequests(G, v, light, Req);
        R.push_back(v);
      }
      relaxRequests(Req);
    }
    std::list<std::pair<Vertex, Weight>> Req;
    for (auto v = R.begin(); v != R.end();) {
      findRequests(G, *v, heavy, Req);
      R.erase(v++);
    }
    relaxRequests(Req);
  }
  delete[] heavy;
  delete[] light;
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
uint64_t ParallelDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::relaxations() const {
  return relaxations_;
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
inline void ParallelDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::findRequests(const Graph<Weight, INFINITE, Vertex, nullvertex, Size>& G, Vertex w, std::list<Vertex>* kind, std::list<std::pair<Vertex, Weight>>& Req) {
  Weight tent_w = tent[w];
  std::list<Vertex>& kind_w = kind[w];
  for (Vertex v : kind_w) {
    Req.emplace_back(v, tent_w + G[w][v].weight);
  }
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
inline void ParallelDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::relaxRequests(std::list<std::pair<Vertex, Weight>>& Req) {
  for (auto it = Req.begin(); it != Req.end();) {
    relax(it->first, it->second);
    Req.erase(it++);
  }
}

template <typename Weight, Weight IDENTITY, Weight INFINITE, typename Vertex, Vertex nullvertex, typename Size>
inline void ParallelDeltaStepping<Weight, IDENTITY, INFINITE, Vertex, nullvertex, Size>::relax(Vertex w, Weight x) {
  pthread_mutex_lock(&relax_mutex);
  relaxations_++;
  Weight& tent_w = tent[w];
  if (x < tent_w) {
    if (tent_w < INFINITE) {
      B.remove(Size(floor(double(tent_w)/delta)), w);
    }
    B.insert(Size(floor(double(x)/delta)), w);
    tent_w = x;
  }
  pthread_mutex_unlock(&relax_mutex);
}

} // namespace graph

#endif /* DELTASTEPPING_INL_HPP_ */
