#include <limits>
#include <set>
#include <vector>
#include <ranges>

template<template <class...> class Container, template<class, class> class P, class T, class U>
std::vector<U> dijkstra(std::span<Container<P<T, U>>> graph, T source) {
  std::vector<U> distance(graph.size(), std::numeric_limits<U>::max());
  distance[source] = 0;
  std::set<std::pair<U, T>> vertices;
  vertices.emplace(0, source);
  do {
    auto vertex = vertices.begin()->second;
    vertices.erase(vertices.begin());
    for (auto [next, weight] : graph[vertex]) {
      if (distance[next] > distance[vertex] + weight) {
        vertices.erase({distance[next], next});
        distance[next] = distance[vertex] + weight;
        vertices.emplace(distance[next], next);
      }
    }
  } while (!vertices.empty());
  return distance;
}

template<std::ranges::contiguous_range R, class T>
auto dijkstra(R&& r, T source) {
  return dijkstra(std::span<std::ranges::range_value_t<R>>(r), source);
}
