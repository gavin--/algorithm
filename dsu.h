#include <cstddef>
#include <type_traits>
#include <vector>

template <class T, bool B = std::is_signed<T>::value>
class Dsu;

template <class T>
class Dsu<T, false> {
 private:
  std::vector<T> parent_, size_;
 public:
  Dsu(std::size_t size) : parent_([&]() {
    std::vector<T> parent;
    parent.reserve(size);
    for (std::size_t i = 0; i < size; ++i) {
      parent.emplace_back(i);
    }
    return parent;
  }()), size_(size, 1), {}

  T Find(T vertex) {
    while (parent_[vertex] != vertex) {
      parent_[vertex] = parent_[parent_[vertex]];
      vertex = parent_[vertex];
    }
    return vertex;
  }

  bool Union(T left, T right) {
    left = Find(left);
    right = Find(right);
    if (left == right) {
      return false;
    }
    size_[left] += size_[right];
    parent_[right] = left;
    return true;
  }

  T Size(T vertex) {
    return size_[Find(vertex)];
  }
};

template <class T>
class Dsu<T, true> {
 private:
  std::vector<T> parent_or_size_;
 public:
  Dsu(std::size_t size) : parent_or_size_(size, -1) {}

  T Find(T vertex) {
    auto root = vertex;
    while (parent_or_size_[root] > 0) {
      root = parent_or_size_[root];
    }
    while (parent_or_size_[vertex] > 0) {
      auto parent = parent_or_size_[vertex];
      parent_or_size_[vertex] = root;
      vertex = parent;
    }
    return root;
  }

  bool Union(T left, T right) {
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
    return -parent_or_size_[Find(vertex)];
  }
};
