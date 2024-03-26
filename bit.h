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
  Bit(std::size_t size) : tree_(size + 1) {}
  
  Bit(const std::vector<T>& tree) : Bit(tree.size() + 1) {
    for (std::size_t i = 1; i <= tree.size(); ++i) {
      tree_[i] += tree[i - 1];
      if (auto parent = i + lowbit(i); parent < tree_.size()) {
        tree_[parent] += tree_[i];
      }
    }
  }
  
  T query(std::size_t index) {
    T result = 0;
    for (++index; index > 0; index -= lowbit(index)) {
      result += tree_[index];
    }
    return result;
  }
  
  void update(std::size_t index, T value) {
    for (++index; index < tree_.size(); index += lowbit(index)) {
      tree_[index] += value;
    }
  }
};
