#include <cassert>
#include <cstddef>
#include <limits>
#include <type_traits>
#include <vector>

template <class T, bool = std::is_signed<T>::value>
class Dsu;

template <class T>
class Dsu<T, false> {
 public:
  Dsu(std::size_t size) : parent_or_size_(size, 1), is_parent_(size, false) {}

  T Find(T vertex) {
    assert(0 <= vertex && vertex < parent_or_size_.size());
    while (is_parent_[vertex]) {
      if (is_parent_[parent_or_size_[vertex]]) {
        parent_or_size_[vertex] = parent_or_size_[parent_or_size_[vertex]];
      }
      vertex = parent_or_size_[vertex];
    }
    return vertex;
  }

  bool Union(T left, T right) {
    left = Find(left);
    right = Find(right);
    if (left == right) {
      return false;
    }
    parent_or_size_[left] += parent_or_size_[right];
    parent_or_size_[right] = left;
    is_parent_[right] = true;
    return true;
  }

  T Size(T vertex) {
    return parent_or_size_[Find(vertex)];
  }

 private:
  std::vector<T> parent_or_size_;
  std::vector<bool> is_parent_;
};

template <class T>
class Dsu<T, true> {
 public:
  Dsu(std::size_t size) : parent_or_size_(size, -1) {}

  T Find(T vertex) {
    assert(0 <= vertex && vertex < parent_or_size_.size());
    while (parent_or_size_[vertex] >= 0) {
      if (parent_or_size_[parent_or_size_[vertex]] >= 0) {
        parent_or_size_[vertex] = parent_or_size_[parent_or_size_[vertex]];
      }
      vertex = parent_or_size_[vertex];
    }
    return vertex;
  }

  bool Union(T left, T right) {
    assert(0 <= left && left < parent_or_size_.size());
    assert(0 <= right && right < parent_or_size_.size());
    left = Find(left);
    right = Find(right);
    if (left == right) {
      return false;
    }
    parent_or_size_[left] += parent_or_size_[right];
    parent_or_size_[right] = left;
    return true;
  }

  T Size(T vertex) {
    auto size = parent_or_size_[Find(vertex)];
    assert(size > std::numeric_limits<T>::min());
    return -size;
  }

 private:
  std::vector<T> parent_or_size_;
};
