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
          for (std::size_t i = 1, j = 0; i < w.size(); ++i) {
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
    for (std::size_t i = 0, j = 0; i < s.size(); ++i) {
      while (j > 0 && w_[j] != s[i]) {
        j = t_[j - 1];
      }
      if (w_[j] == s[i]) {
        ++j;
      }
      if (j == w_.size()) {
        return i + 1 - w_.size();
      }
    }
    return std::string::npos;
  }

 private:
  const std::basic_string_view<T> w_;
  const std::vector<std::size_t> t_;
};
