template<class T>
T sqrt(T n) {
  auto result = n, next = (result + n / result) / 2;
  while (result < next) {
    result = next;
    next = (result + n / result) / 2;
  }
  return result;
}
