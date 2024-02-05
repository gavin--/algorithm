#include <vector>

template<class T>
std::vector<T> sieve(T size) {
  std::vector<T> primes;
  std::vector<bool> composite(size);
  for (T i = 2; i < size; ++i) {
    if (!composite[i]) {
      primes.push_back(i);
    }
    for (T j = 0; j < primes.size() && i * primes[j] < size; ++j) {
      composite[i * primes[j]] = true;
      if (i % primes[j] == 0) {
        break;
      }
    }
  }
  return primes;
}
