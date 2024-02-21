#include <vector>

template <class T>
class Dsu {
  private:
    std::vector<T> parent_, size_;

  public:
    Dsu(T size) : size_(size, 1), parent_([&]() {
      std::vector<T> parent;
      parent.reserve(size);
      for (T i = 0; i < size; ++i) {
        parent.emplace_back(i);
      }
      return parent;
    }()) {}

    T Find(T vertex) {
      while (parent_[vertex] != vertex) {
        parent_[vertex] = parent_[parent_[vertex]];
        vertex = parent_[vertex];
      }
      return vertex;
    }

    void Union(T left, T right) {
      left = Find(left), right= Find(right);
      if (left == right) {
        return;
      }
      if (size_[left] < size_[right]) {
        std::swap(left, right);
      }
      parent_[right] = left;
      size_[left] += size_[right];
    }

    T size(T vertex) {
      return size_[Find(vertex)];
    }
};
