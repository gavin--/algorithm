#include <cassert>
#include <type_traits>

template <class T, class U>
T Pow(T base, U exp) {
  assert(exp >= 0);
  T result = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = result * base;
    }
    base = base * base;
    exp /= 2;
  }
  return result;
}

template <class T, class U, class V>
std::common_type_t<T, U> Pow(T base, U exp, V mod) {
  assert(exp >= 0);
  T result = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = result * base % mod;
    }
    base = base * base % mod;
    exp /= 2;
  }
  return result;
}
