#include <cstddef>
#include <type_traits>
#include <vector>

template <class T, bool = std::is_signed<T>::value>
class Dsu;

template <class T>
class Dsu<T, false> {
 private:
  std::vector<T> parent_or_size_;
  std::vector<bool> is_parent_;

 public:
  Dsu(std::size_t size) : parent_or_size_(size, 1), is_parent_(size, false) {}

  T Find(std::size_t vertex) {
    while (is_parent_[vertex]) {
      if (is_parent_[parent_or_size_[vertex]]) {
        parent_or_size_[vertex] = parent_or_size_[parent_or_size_[vertex]];
      } else {
        parent_or_size_[vertex] = parent_or_size_[vertex];
      }
      vertex = parent_or_size_[vertex];
    }
    return vertex;
  }

  bool Union(std::size_t left, std::size_t right) {
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

  T Size(std::size_t vertex) { return parent_or_size_[Find(vertex)]; }
};

template <class T>
class Dsu<T, true> {
 private:
  std::vector<T> parent_or_size_;

 public:
  Dsu(std::size_t size) : parent_or_size_(size, -1) {}

  T Find(std::size_t vertex) {
    while (parent_or_size_[vertex] > 0) {
      if (parent_or_size_[parent_or_size_[vertex]] > 0) {
        parent_or_size_[vertex] = parent_or_size_[parent_or_size_[vertex]];
      } else {
        parent_or_size_[vertex] = parent_or_size_[vertex];
      }
      vertex = parent_or_size_[vertex];
    }
    return vertex;
  }

  bool Union(std::size_t left, std::size_t right) {
    left = Find(left);
    right = Find(right);
    if (left == right) {
      return false;
    }
    parent_or_size_[left] += parent_or_size_[right];
    parent_or_size_[right] = left;
    return true;
  }

  T Size(std::size_t vertex) { return -parent_or_size_[Find(vertex)]; }
};
