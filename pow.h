#include <cassert>
#include <type_traits>

template <class T, class U>
std::common_type_t<T, U> Pow(T base, U exp) {
  assert(exp >= 0);
  std::common_type_t<T, U> result = 1, b = base;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = result * b;
    }
    b = b * b;
    exp /= 2;
  }
  return result;
}

template <class T, class U, class V>
std::common_type_t<T, U, V> Pow(T base, U exp, V mod) {
  assert(exp >= 0);
  std::common_type_t<T, U, V> result = 1, b = base;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = result * b % mod;
    }
    b = b * b % mod;
    exp /= 2;
  }
  return result;
}
