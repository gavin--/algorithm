template<class T>
T sqrt(T n) {
  if (n <= 1) {
    return n;
  }
  auto result = n / 2, next = (result + n / result) / 2;
  while (result < next) {
    result = next;
    next = (result + n / result) / 2;
  }
  return result;
}
