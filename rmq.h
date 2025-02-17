#include <cassert>
#include <limits>
#include <span>
#include <vector>

template <class T>
class SqrtDecomposition {
public:
  SqrtDecomposition(std::span<T> data) : block_size_(sqrt(data.size())), data_(data) {
    assert(!data.empty());
    auto size = (data.size() - 1) / block_size_ + 1;
    blocks_.reserve(size);
    for (std::size_t i = 0; i < size; ++i) {
      T block = std::numeric_limits<T>::max();
      for (std::size_t j = i * block_size_; j < std::min(data_.size(), (i + 1) * block_size_); ++j) {
        block = std::min(block, data_[j]);
      }
      blocks_.push_back(block);
    }
  }

  auto Query(std::size_t l, std::size_t r) {
    assert(l >= 0 && r > l);
    T result = std::numeric_limits<T>::max();
    auto block_begin = (l == 0 ? 0 : (l - 1) / block_size_ + 1), block_end = r / block_size_;
    if (block_begin < block_end) {
      for (std::size_t i = l; i < block_begin * block_size_; ++i) {
        result = std::min(result, data_[i]);
      }
      for (std::size_t i = block_begin; i < block_end; ++i) {
        result = std::min(result, blocks_[i]);
      }
      for (std::size_t i = l; i < block_begin * block_size_; ++i) {
        result = std::min(result, data_[i]);
      }
    } else {
      for (std::size_t i = l; i < r; ++i) {
        result = std::min(result, data_[i]);
      }
    }
    return result;
  }
private:
  const std::size_t block_size_;
  std::span<T> data_;
  std::vector<T> blocks_;
};
