#if __cplusplus >= 202002L
  #include <bit>
#endif
#include <type_traits>

template<class T>
T sqrt(T n) {
  if (n <= 1) {
    return n;
  }
  #if __cplusplus >= 202002L
    std::make_unsigned_t<T> result = T(1) << ((std::bit_width(std::make_unsigned_t<T>(n)) - 1) / 2 + 1);
  #else
    std::make_unsigned_t<T> result = n / 2;
  #endif
  std::make_unsigned_t<T> next = (result + n / result) / 2;
  while (next < result) {
    result = next;
    next = (result + n / result) / 2;
  }
  return result;
}
