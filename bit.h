#include <cassert>
#include <cstddef>
#include <ranges>
#include <span>
#include <vector>

template <class T>
class Bit {
 public:
  explicit Bit(std::size_t size) : tree_(size) {}

  template <std::ranges::contiguous_range R>
    requires std::ranges::sized_range<R>
  explicit Bit(R&& tree)
      : Bit(std::span<const std::ranges::range_value_t<R>>(tree)) {}

  T Query(std::size_t index) const {
    assert(index <= tree_.size());
    T result = 0;
    for (; index > 0; index -= index & -index) {
      result += tree_[index - 1];
    }
    return result;
  }

  void Update(std::size_t index, T value) {
    assert(index < tree_.size());
    for (; index < tree_.size(); index = index | (index + 1)) {
      tree_[index] += value;
    }
  }

 private:
  std::vector<T> tree_;
  explicit Bit(std::span<const T> tree) : Bit(tree.size()) {
    for (std::size_t i = 0; i < tree_.size(); ++i) {
      tree_[i] += tree[i];
      if (auto parent = i | (i + 1); parent < tree_.size()) {
        tree_[parent] += tree_[i];
      }
    }
  }
};
