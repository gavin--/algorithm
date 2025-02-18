#include <limits>
#include <map>
#include <set>
#include <vector>

template <class U, class Neighbors, class T>
std::map<T, U> dijkstra(const std::map<T, Neighbors>& graph, const T& source) {
  std::map<T, U> distance;
  distance[source] = 0;
  std::set<std::pair<U, T>> q;
  q.emplace(0, source);
  do {
    auto [dist_v, v] = *q.begin();
    q.erase(q.begin());
    for (const auto& [u, w] : graph.at(v)) {
      if (auto it = distance.find(u); it == distance.end()) {
        distance[u] = dist_v + w;
        q.emplace(dist_v + w, u);
      } else if (it->second > dist_v + w) {
        q.erase({it->second, u});
        it->second = dist_v + w;
        q.emplace(it->second, u);
      }
    }
  } while (!q.empty());
  return distance;
}

template <class U, class Neighbors, class T>
std::vector<U> dijkstra(const std::vector<Neighbors>& graph, const T& source) {
  std::vector<U> distance(graph.size(), std::numeric_limits<U>::max());
  distance[source] = 0;
  std::set<std::pair<U, T>> q;
  q.emplace(0, source);
  do {
    auto v = q.begin()->second;
    q.erase(q.begin());
    for (const auto& [u, w] : graph[v]) {
      if (distance[u] > distance[v] + w) {
        q.erase({distance[u], u});
        distance[u] = distance[v] + w;
        q.emplace(distance[u], u);
      }
    }
  } while (!q.empty());
  return distance;
}
