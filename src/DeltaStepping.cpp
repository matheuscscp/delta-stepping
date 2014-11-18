/*
 * DeltaStepping.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: Pimenta
 */

#include <list>
#include <vector>
#include <cmath>

#include "DeltaStepping.hpp"

#define DELTA 5

using namespace std;

struct DeltaStepping {
  // in
  const Graph& G;
  Vertex source;
  
  // local
  map<Vertex, list<Vertex>> heavy, light;
  vector<list<Vertex>> B;
  
  // out
  Weight* tent; // tentative distance. equals distance after the algorithm
  
  DeltaStepping(const Graph& G, Vertex source, Weight* tent) :
  G(G), source(source), tent(tent)
  {
    algorithm();
  }
  
  void algorithm() {
    for (auto& v : G) {
      list<Vertex>& h = heavy[v.vertex];
      list<Vertex>& l = light[v.vertex];
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
      list<Vertex> S;
      while (B[i].size() > 0) {
        list<pair<Vertex, Weight>> Req;
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
      list<pair<Vertex, Weight>> Req;
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
  
  void relax(const Vertex& v, Weight x) {
    Weight& tent_v = tent[v];
    if (x < tent_v) {
      size_t floor_tent_v_delta = size_t(floor(double(tent_v)/DELTA));
      if (floor_tent_v_delta < B.size()) {
        B[floor_tent_v_delta].remove(v);
      }
      size_t floor_x_delta = size_t(floor(double(x)/DELTA));
      if (floor_x_delta >= B.size()) {
        B.insert(B.end(), floor_x_delta + 1 - B.size(), list<Vertex>());
      }
      B[floor_x_delta].push_back(v);
      tent_v = x;
    }
  }
};

void serial_deltaStepping(const Graph& G, Vertex source, Weight* dist) {
  DeltaStepping(G, source, dist);
}
