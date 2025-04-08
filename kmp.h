#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

template <class T>
class Kmp {
 public:
  explicit Kmp(std::basic_string_view<T> w)
      : w_(w), t_([](auto w) {
          std::vector<std::size_t> t(w.size());
          for (std::size_t i = 1; i < w.size(); ++i) {
            std::size_t j = t[i - 1];
            while (j > 0 && w[i] != w[j]) {
              j = t[j - 1];
            }
            if (w[i] == w[j]) {
              ++j;
            }
            t[i] = j;
          }
          return t;
        }(w)) {}

  std::size_t Find(std::basic_string_view<T> s) const {
    for (std::size_t i = 0, k = 0; i < s.size(); ++i) {
      while (k > 0 && w_[k] != s[i]) {
        k = t_[k - 1];
      }
      if (w_[k] == s[i]) {
        ++k;
      }
      if (k == w_.size()) {
        return i + 1 - w_.size();
      }
    }
    return std::string::npos;
  }

 private:
  const std::basic_string_view<T> w_;
  const std::vector<std::size_t> t_;
};
