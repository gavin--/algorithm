#include <limits>
#include <map>
#include <set>
#include <vector>

template <class U, class Neighbors, class T>
U prim(const std::vector<Neighbors>& graph, const T& source) {
  U result = 0;
  std::vector<bool> selected(graph.size());
  std::vector<U> dist(graph.size(), std::numeric_limits<U>::max());
  dist[source] = 0;
  std::set<std::pair<U, T>> q;
  q.emplace(0, source);
  do {
    auto v = q.begin()->second;
    selected[v] = true;
    result += q.begin()->first;
    q.erase(q.begin());
    for (auto [u, w] : graph[v]) {
      if (!selected[u] && w < dist[u]) {
        q.erase({dist[u], u});
        dist[u] = w;
        q.emplace(w, u);
      }
    }
  } while (!q.empty());
  return result;
}

template <class U, class Neighbors, class T>
U prim(const std::map<T, Neighbors>& graph, const T& source) {
  U result = 0;
  std::set<T> selected;
  std::map<T, U> dist;
  dist[source] = 0;
  std::set<std::pair<U, T>> q;
  q.emplace(0, source);
  do {
    auto v = q.begin()->second;
    selected.emplace(v);
    result += q.begin()->first;
    q.erase(q.begin());
    for (auto [u, w] : graph.at(v)) {
      if (selected.count(u) == 0) {
        if (auto it = dist.find(u); it == dist.end()) {
          dist[u] = w;
          q.emplace(w, u);
        } else if (w < it->second) {
          q.erase({it->second, u});
          it->second = w;
          q.emplace(dist[u], u);
        }
      }
    }
  } while (!q.empty());
  return result;
}
