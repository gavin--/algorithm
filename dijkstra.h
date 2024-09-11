#include <limits>
#include <set>
#include <vector>

#include "graph.h"

template<class U, class Neighbors, class T>
std::vector<U> dijkstra(const Graph<Neighbors>& graph, const T& source) {
  std::vector<U> distance(graph.size(), std::numeric_limits<U>::max());
  distance[source] = 0;
  std::set<std::pair<U, T>> q;
  q.emplace(0, source);
  do {
    auto v = q.begin()->second;
    q.erase(q.begin());
    for (auto [u, w] : graph[v]) {
      if (distance[u] > distance[v] + w) {
        q.erase({distance[u], u});
        distance[u] = distance[v] + w;
        q.emplace(distance[u], u);
      }
    }
  } while (!q.empty());
  return distance;
}

template<template<class, class> class Map, template <class...> class Container, template<class, class> class P, class T, class U>
Map<T, U> dijkstra(const Map<T, Container<P<T, U>>>& graph, T source) {
  Map<T, U> distance;
  distance[source] = 0;
  std::set<std::pair<U, T>> s;
  s.emplace(0, source);
  do {
    auto vertex = s.begin()->second;
    auto dist = distance[vertex];
    s.erase(s.begin());
    for (auto [next, weight] : graph.at(vertex)) {
      auto& next_dist = distance[next];
      if (next_dist > dist + weight) {
        s.erase({next_dist, next});
        next_dist = dist + weight;
        s.emplace(next_dist, next);
      }
    }
  } while (!s.empty());
  return distance;
}

