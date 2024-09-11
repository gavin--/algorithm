#include <vector>

template<class Neighbors>
class Graph {
public:
  Graph(std::size_t size) : graph_(size) {}
  Neighbors& operator[](std::size_t pos) {
    return graph_[pos];
  }
  const Neighbors& operator[](std::size_t pos) const {
    return graph_[pos];
  }
private:
  std::vector<Neighbors> graph_;
};
