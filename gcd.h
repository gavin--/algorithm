#include <cassert>
#include <numeric>
#include <tuple>
#include <type_traits>
#include <utility>

template <class M, class N>
std::pair<std::common_type_t<M, N>, std::common_type_t<M, N>> extended_gcd(
    M m, N n) {
  std::common_type_t<M, N> t = 0, next_t = 1, r = n, next_r = m;
  while (next_r != 0) {
    auto q = r / next_r;
    std::tie(t, next_t) = std::make_tuple(next_t, t - q * next_t);
    std::tie(r, next_r) = std::make_tuple(next_r, r - q * next_r);
  }
  return {r, t};
}

// Returns a positive multiplicative inverse of `a` modulo `n`.
template <class M, class N>
std::common_type_t<M, N> inverse(M a, N n) {
  assert(std::gcd(a, n) == 1);
  auto result = extended_gcd(a, n).second;
  if (result < 0) {
    result += n;
  }
  return result;
}
