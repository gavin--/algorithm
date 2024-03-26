#include <cstddef>
#include <vector>

template <class T>
class Bit {
 private:
  std::vector<T> tree_;
  
  std::size_t lowbit(std::size_t n) {
    return n & -n;
  }
 public:
  Bit(std::size_t size) : tree_(size) {}
  
  Bit(const std::vector<T>& tree) : Bit(tree.size()) {
    for (std::size_t i = 1; i < tree.size(); ++i) {
      tree_[i] += tree[i];
      if (auto parent = i + lowbit(i); parent < tree.size()) {
        tree_[parent] += tree_[i];
      }
    }
  }
  
  T query(std::size_t index) {
    T result = 0;
    while (index > 0) {
      result += tree_[index];
      index -= lowbit(index);
    }
    return result;
  }
  
  void update(std::size_t index, T value) {
    while (index < tree_.size()) {
      tree_[index] += value;
      index += lowbit(index);
    }
  }
};
