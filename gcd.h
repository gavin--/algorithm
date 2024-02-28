#include <tuple>

template<class T>
T gcd(T a, T b) {
  while (b != 0) {
    auto t = b;
    b = a % b;
    a = t;
  }
  return a;
}

template<class T>
T inverse(T a, T b) {
  auto t = 0, next_t = 1, r = b, next_r = a;
  while (next_r != 0) {
    auto q = r / next_r;
    std::tie(t, next_t) = std::make_tuple(next_t, t - q * next_t);
    std::tie(r, next_r) = std::make_tuple(next_r, r - q * next_r);
  }
  if (t < 0) {
    t += b;
  }
  return t;
}
