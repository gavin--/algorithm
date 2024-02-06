#include <limits>
#include <set>
#include <vector>
#include <ranges>

template<template <class...> class Container, template<class, class> class P, class T, class U>
std::vector<U> dijkstra(std::span<const Container<P<T, U>>> graph, T source) {
  std::vector<U> distance(graph.size(), std::numeric_limits<U>::max());
  distance[source] = 0;
  std::set<std::pair<U, T>> s;
  s.emplace(0, source);
  do {
    auto vertex = s.begin()->second;
    s.erase(s.begin());
    for (auto [next, weight] : graph[vertex]) {
      if (distance[next] > distance[vertex] + weight) {
        s.erase({distance[next], next});
        distance[next] = distance[vertex] + weight;
        s.emplace(distance[next], next);
      }
    }
  } while (!s.empty());
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
    s.erase(s.begin());
    for (auto [next, weight] : graph.at(vertex)) {
      if (distance[next] > distance[vertex] + weight) {
        s.erase({distance[next], next});
        distance[next] = distance[vertex] + weight;
        s.emplace(distance[next], next);
      }
    }
  } while (!s.empty());
  return distance;
}

template<std::ranges::contiguous_range R, class T>
auto dijkstra(R&& r, T source) {
  return dijkstra(std::span<const std::ranges::range_value_t<R>>(r), source);
}
