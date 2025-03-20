#include <chrono>

class Timer {
 public:
  auto Stop() const {
    return std::chrono::high_resolution_clock::now() - start_time_;
  }
  void Reset() { start_time_ = std::chrono::high_resolution_clock::now(); }

 private:
  std::chrono::high_resolution_clock::time_point start_time_ =
      std::chrono::high_resolution_clock::now();
};
