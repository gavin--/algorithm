#include <vector>

template<class T>
vector<T> sieve(T size) {
  vector<T> primes;
  vector<bool> composite(size);
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
