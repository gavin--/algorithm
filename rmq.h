#include <bit>
#include <cassert>
#include <limits>
#include <random>
#include <span>
#include <vector>

template <class T>
class SqrtDecomposition {
 public:
  SqrtDecomposition(std::span<T> data)
      : block_size_(sqrt(data.size())), data_(data), blocks_([this, &data]() {
          assert(!data.empty());
          std::vector<T> blocks((data.size() - 1) / block_size_ + 1,
                                std::numeric_limits<T>::max());
          for (std::size_t i = 0; i < blocks.size(); ++i) {
            for (std::size_t j = i * block_size_;
                 j < std::min(data_.size(), (i + 1) * block_size_); ++j) {
              blocks[i] = std::min(blocks[i], data_[j]);
            }
          }
          return blocks;
        }()) {}

  auto Query(std::size_t l, std::size_t r) const {
    assert(l >= 0 && r > l);
    T result = std::numeric_limits<T>::max();
    auto block_begin = (l == 0 ? 0 : (l - 1) / block_size_ + 1),
         block_end = r / block_size_;
    if (block_begin < block_end) {
      for (std::size_t i = l; i < block_begin * block_size_; ++i) {
        result = std::min(result, data_[i]);
      }
      for (std::size_t i = block_begin; i < block_end; ++i) {
        result = std::min(result, blocks_[i]);
      }
      for (std::size_t i = block_end * block_size_; i < r; ++i) {
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
  const std::span<T> data_;
  const std::vector<T> blocks_;
};

template <class T>
class SparseTable {
 public:
  SparseTable(std::span<T> data)
      : sparse_table_([&data]() {
          assert(!data.empty());
          std::vector<std::vector<T>> sparse_table;
          sparse_table.resize(std::bit_width(data.size()));
          sparse_table.front().reserve(data.size());
          sparse_table.front().insert(sparse_table.front().end(), data.begin(),
                                      data.end());
          for (std::size_t i = 1; i < sparse_table.size(); ++i) {
            sparse_table[i].resize(data.size() - (1 << i) + 1);
            for (std::size_t j = 0; j + (1 << i) <= data.size(); ++j) {
              sparse_table[i][j] =
                  std::min(sparse_table[i - 1][j],
                           sparse_table[i - 1][j + (1 << (i - 1))]);
            }
          }
          return sparse_table;
        }()) {}

  auto Query(std::size_t l, std::size_t r) const {
    assert(l >= 0 && r > l);
    auto log = std::bit_width(r - l) - 1;
    return std::min(sparse_table_[log][l], sparse_table_[log][r - (1 << log)]);
  }

 private:
  const std::vector<std::vector<T>> sparse_table_;
};
