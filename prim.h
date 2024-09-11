#include <limits>
#include <set>
#include <vector>

template<class U, class Neighbors, class T>
U prim(const std::vector<Neighbors>& graph, const T& source) {
  U result = 0;
  std::vector<bool> selected(graph.size());
  std::vector<U> dist(graph.size(), std::numeric_limits<U>::max());
  dist[source] = 0;
  std::set<std::pair<U, T>> edges;
  edges.emplace(0, source);
  do {
    auto v = edges.begin()->second;
    selected[v] = true;
    result += edges.begin()->first;
    edges.erase(edges.begin());
    for (auto [u, w] : graph[v]) {
      if (!selected[u] && w < dist[u]) {
        edges.erase({dist[u], u});
        dist[u] = w;
        edges.emplace(w, u);
      }
    }
  } while (!edges.empty());
  return result;
}
