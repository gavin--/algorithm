#include <bit>
#include <cassert>
#include <type_traits>

template <class T>
T sqrt(T n) {
  assert(n >= 0);
  if (n <= 1) {
    return n;
  }
  auto result =
      T(1) << ((std::bit_width(std::make_unsigned_t<T>(n)) - 1) / 2 + 1);
  auto next = (result + n / result) / 2;
  while (next < result) {
    result = next;
    next = (result + n / result) / 2;
  }
  return result;
}
