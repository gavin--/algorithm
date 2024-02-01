template<class T>
T sqrt(T n) {
  T begin = 0, end = n;
  while (begin < end) {
    auto mid = (end + begin + 1) / 2;
    if (mid <= n / mid) {
      begin = mid;
    } else {
      end = mid - 1;
    }
  }
  return end;
}
