/*
 * DeltaStepping.inl.hpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Pimenta
 */

#ifndef DELTASTEPPING_INL_HPP_
#define DELTASTEPPING_INL_HPP_

#include <queue>
#include <cmath>

#include "ThreadManager.hpp"

namespace graph {

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
SerialDeltaStepping<Weight, Vertex, nullvertex, Size>::SerialDeltaStepping() : delta(0), tent(nullptr), relaxations_(0) {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
void SerialDeltaStepping<Weight, Vertex, nullvertex, Size>::run(const Graph<Weight, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist) {
  std::list<Vertex>* heavy = new std::list<Vertex>[G.order() + 1];
  std::list<Vertex>* light = new std::list<Vertex>[G.order() + 1];
  delta = 1.0f/G.maxdegree();
  B.init(Size(ceil(G.maxweight()/delta))*3 + 1);//FIXME
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
    tent[v.vertex] = Weight(0x7fffffff);
  }
  relax(source, 0);
  Size i = 0;
  while (B.totalvertices() > 0) {
    i = B.firstnonempty(i);
    std::list<Vertex> R;
    while (B.size(i) > 0) {
      std::list<std::pair<Vertex, Weight>> Req;
      std::shared_ptr<std::list<Vertex>> tmp = B.pop(i);
      for (auto v = tmp->begin(); v != tmp->end();) {
        findRequests(G, *v, light, Req);
        R.push_back(*v);
        tmp->erase(v++);
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

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
uint64_t SerialDeltaStepping<Weight, Vertex, nullvertex, Size>::relaxations() const {
  return relaxations_;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
inline void SerialDeltaStepping<Weight, Vertex, nullvertex, Size>::findRequests(const Graph<Weight, Vertex, nullvertex, Size>& G, Vertex w, std::list<Vertex>* kind, std::list<std::pair<Vertex, Weight>>& Req) {
  Weight tent_w = tent[w];
  std::list<Vertex>& kind_w = kind[w];
  for (Vertex v : kind_w) {
    Req.emplace_back(v, tent_w + G[w][v].weight);
  }
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
inline void SerialDeltaStepping<Weight, Vertex, nullvertex, Size>::relaxRequests(std::list<std::pair<Vertex, Weight>>& Req) {
  for (auto it = Req.begin(); it != Req.end();) {
    relax(it->first, it->second);
    Req.erase(it++);
  }
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
inline void SerialDeltaStepping<Weight, Vertex, nullvertex, Size>::relax(Vertex w, Weight x) {
  relaxations_++;
  if (x < tent[w]) {
    if (tent[w] < Weight(0x7fffffff)) {
      B.remove(Size(floor(tent[w]/delta)), w);
    }
    B.insert(Size(floor(x/delta)), w);
    tent[w] = x;
  }
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
ParallelDeltaStepping<Weight, Vertex, nullvertex, Size>::ParallelDeltaStepping(Size threshold) : threshold(threshold), delta(0), tent(nullptr), relaxations_(0) {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
ParallelDeltaStepping<Weight, Vertex, nullvertex, Size>::~ParallelDeltaStepping() {
  
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
void ParallelDeltaStepping<Weight, Vertex, nullvertex, Size>::run(const Graph<Weight, Vertex, nullvertex, Size>& G, Vertex source, Weight* dist) {
  int nth = ThreadManager::nthreads();
  std::list<Vertex>* heavy = new std::list<Vertex>[G.order() + 1];
  std::list<Vertex>* light = new std::list<Vertex>[G.order() + 1];
  std::queue<Vertex>* Q = new std::queue<Vertex>[nth];
  delta = 1.0f/G.maxdegree();
  Size bsize = Size(ceil(G.maxweight()/delta))*3 + 1;//FIXME
  B.init(bsize);
  tent = dist;
  // parallel initialization
  {
    JobPool jobs;
    for (int tid = 0; tid < nth; tid++) {
      jobs.dispatch([&G, tid, nth, heavy, light, this]() {
        Size V = G.order(), quo = V/nth, rem = V%nth;
        Vertex first = tid*quo + 1, last = (tid + 1)*quo;
        if (rem != 0) {
          Size W = quo + 1;
          if (tid < rem) {
            first = tid*W + 1;
            last = (tid + 1)*W;
          }
          else {
            first = rem*W + (tid - rem)*quo + 1;
            last = rem*W + (tid + 1 - rem)*quo;
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
          tent[v.vertex] = Weight(0x7fffffff);
        }
      });
    }
  }
  relax(source, 0);
  Size i = 0;
  while (B.totalvertices() > 0 && B.totalvertices() < threshold) {
    i = B.firstnonempty(i);
    std::list<Vertex> R;
    while (B.size(i) > 0) {
      std::list<std::pair<Vertex, Weight>> Req;
      std::shared_ptr<std::list<Vertex>> tmp = B.pop(i);
      for (auto v = tmp->begin(); v != tmp->end();) {
        findRequests(G, *v, light, Req);
        R.push_back(*v);
        tmp->erase(v++);
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
  // parallel section
  BucketArray<Vertex, Size>* localB = new BucketArray<Vertex, Size>[nth];
  {
    JobPool jobs;
    for (int tid = 0; tid < nth; tid++) {
      localB[tid].init(bsize);
    }
    for (Size i = 0; i < bsize; i++) {
      std::shared_ptr<std::list<Vertex>> bucket = B.pop(i);
      for (auto v = bucket->begin(); v != bucket->end();) {
        localB[(*v)%nth].insert(i, *v);
        bucket->erase(v++);
      }
    }
    for (int tid = 0; tid < nth; tid++) {
      jobs.dispatch([&G, localB, tid, light, heavy, this]() {
        BucketArray<Vertex, Size>& tB = localB[tid];
        Size i = 0;
        while (tB.totalvertices() > 0) {
          i = tB.firstnonempty(i);
          std::list<Vertex> R;
          while (tB.size(i) > 0) {
            std::list<std::pair<Vertex, Weight>> Req;
            std::shared_ptr<std::list<Vertex>> tmp = tB.pop(i);
            for (auto v = tmp->begin(); v != tmp->end();) {
              findRequests(G, *v, light, Req);
              R.push_back(*v);
              tmp->erase(v++);
            }
            relaxRequestsLocal(tB, Req);
          }
          std::list<std::pair<Vertex, Weight>> Req;
          for (auto v = R.begin(); v != R.end();) {
            findRequests(G, *v, heavy, Req);
            R.erase(v++);
          }
          relaxRequestsLocal(tB, Req);
        }
      });
    }
  }
  delete[] heavy;
  delete[] light;
  delete[] Q;
  delete[] localB;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
uint64_t ParallelDeltaStepping<Weight, Vertex, nullvertex, Size>::relaxations() const {
  return relaxations_;
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
inline void ParallelDeltaStepping<Weight, Vertex, nullvertex, Size>::findRequests(const Graph<Weight, Vertex, nullvertex, Size>& G, Vertex w, std::list<Vertex>* kind, std::list<std::pair<Vertex, Weight>>& Req) {
  Weight tent_w = tent[w];
  std::list<Vertex>& kind_w = kind[w];
  for (Vertex v : kind_w) {
    Req.emplace_back(v, tent_w + G[w][v].weight);
  }
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
inline void ParallelDeltaStepping<Weight, Vertex, nullvertex, Size>::relaxRequests(std::list<std::pair<Vertex, Weight>>& Req) {
  for (auto it = Req.begin(); it != Req.end();) {
    relax(it->first, it->second);
    Req.erase(it++);
  }
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
inline void ParallelDeltaStepping<Weight, Vertex, nullvertex, Size>::relaxRequestsLocal(BucketArray<Vertex, Size>& tB, std::list<std::pair<Vertex, Weight>>& Req) {
  for (auto it = Req.begin(); it != Req.end();) {
    relaxLocal(tB, it->first, it->second);
    Req.erase(it++);
  }
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
inline void ParallelDeltaStepping<Weight, Vertex, nullvertex, Size>::relax(Vertex w, Weight x) {
  relaxations_++;
  if (x < tent[w]) {
    tent[w] = x;
    if (tent[w] < Weight(0x7fffffff)) {
      B.remove(Size(floor(tent[w]/delta)), w);
    }
    B.insert(Size(floor(x/delta)), w);
  }
}

template <typename Weight, typename Vertex, Vertex nullvertex, typename Size>
inline void ParallelDeltaStepping<Weight, Vertex, nullvertex, Size>::relaxLocal(BucketArray<Vertex, Size>& tB, Vertex w, Weight x) {
  relaxations_++;
  bool swaped = false;
  Weight tmp;
  do {
    tmp = tent[w];
    if (x >= tmp) {
      break;
    }
    swaped = __sync_bool_compare_and_swap((int*)&tent[w], *((int*)&tmp), *((int*)&x));
    if (swaped) {
      break;
    }
  } while (true);
  if (swaped) {
    if (tmp < Weight(0x7fffffff)) {
      tB.remove(Size(floor(tmp/delta)), w);
    }
    tB.insert(Size(floor(x/delta)), w);
  }
}

} // namespace graph

#endif /* DELTASTEPPING_INL_HPP_ */
