template<class T>
T sqrt(T n) {
  if (n <= 1) {
    return n;
  }
  auto result = n, next = (result + n / result) / 2;
  while (next < result) {
    result = next;
    next = (result + n / result) / 2;
  }
  return result;
}
