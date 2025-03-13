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
    for (; index > 0; index -= Lowbit(index)) {
      result += tree_[index - 1];
    }
    return result;
  }

  void Update(std::size_t index, T value) {
    assert(index < tree_.size());
    for (++index; index <= tree_.size(); index += Lowbit(index)) {
      tree_[index - 1] += value;
    }
  }

 private:
  std::vector<T> tree_;
  std::size_t Lowbit(std::size_t n) const { return n & -n; }
  explicit Bit(std::span<const T> tree) : Bit(tree.size()) {
    for (std::size_t i = 1; i <= tree_.size(); ++i) {
      tree_[i - 1] += tree[i - 1];
      if (auto parent = i + Lowbit(i); parent < tree_.size()) {
        tree_[parent] += tree_[i - 1];
      }
    }
  }
};
