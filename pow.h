template<class T>
T pow(T base, T exp) {
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

template<class T>
T pow(T base, T exp, T mod) {
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
