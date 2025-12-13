#include <cassert>
#include <cstddef>
#include <type_traits>
#include <vector>

template <class M, class N>
class Binomial {
 public:
  explicit Binomial(M size, N mod) : mod_(mod) {
    assert(size <= mod);
    factorial_.resize(size, 1);
    inverse_factorial_.resize(size, 1);
    std::vector<N> inv(size, 1);
    for (std::common_type_t<M, N> i = 2; i < size; ++i) {
      factorial_[i] = factorial_[i - 1] * i % mod_;
      inv[i] = (-mod_ / i + mod_) * inv[mod_ % i] % mod_;
      assert(inv[i] > 0);
      inverse_factorial_[i] = inverse_factorial_[i - 1] * inv[i] % mod_;
    }
  }

  std::common_type_t<M, N> C(std::size_t n, std::size_t k) const {
    assert(n < factorial_.size());
    assert(k <= n);
    return factorial_[n] * inverse_factorial_[k] % mod_ *
           inverse_factorial_[n - k] % mod_;
  }

  std::common_type_t<M, N> Factorial(std::size_t i) const {
    assert(i < factorial_.size());
    return factorial_[i];
  }

  std::common_type_t<M, N> InverseFactorial(std::size_t i) const {
    assert(i < inverse_factorial_.size());
    return inverse_factorial_[i];
  }

 private:
  std::vector<std::common_type_t<M, N>> factorial_;
  std::vector<std::common_type_t<M, N>> inverse_factorial_;
  N mod_;
};
