#include <cassert>
#include <cstddef>
#include <limits>
#include <vector>

template <class T>
class Bit {
 public:
  Bit(std::size_t size) : tree_(size + 1) {
    assert(size < std::numeric_limits<std::size_t>::max());
  }

  Bit(const std::vector<T>& tree) : Bit(tree.size()) {
    for (std::size_t i = 1; i < tree_.size(); ++i) {
      tree_[i] += tree[i - 1];
      if (auto parent = i + Lowbit(i); parent < tree_.size()) {
        tree_[parent] += tree_[i];
      }
    }
  }

  T Query(std::size_t index) const {
    assert(index < tree_.size());
    T result = 0;
    for (++index; index > 0; index -= Lowbit(index)) {
      result += tree_[index];
    }
    return result;
  }

  void Update(std::size_t index, T value) {
    assert(index < tree_.size());
    for (++index; index < tree_.size(); index += Lowbit(index)) {
      tree_[index] += value;
    }
  }

 private:
  std::vector<T> tree_;
  std::size_t Lowbit(std::size_t n) { return n & -n; }
};
