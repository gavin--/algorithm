#include <vector>

template <class T>
std::vector<T> Sieve(std::size_t size) {
  std::vector<T> primes;
  std::vector<bool> composite(size);
  for (std::size_t i = 2; i < size; ++i) {
    if (!composite[i]) {
      primes.push_back(i);
    }
    for (std::size_t j = 0; j < primes.size() && i * primes[j] < size; ++j) {
      composite[i * primes[j]] = true;
      if (i % primes[j] == 0) {
        break;
      }
    }
  }
  return primes;
}
