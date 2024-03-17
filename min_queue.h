#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

template<class T, class Compare = std::less<T>>
class MinQueue {
  protected:
   std::vector<std::pair<T, T>> left_, right_;
 public:
  auto empty() const {
    return left_.empty() && right_.empty();
  }
  
  auto size() const {
    return left_.size() + right_.size();
  }
  
  auto front() const {
    if (left_.empty()) {
      return right_.back().first;
    }
    return left_.front().first;
  }
  
  auto back() const {
    if (right_.empty()) {
      return left_.back().first;
    }
    return right_.front().first;
  }
  
  auto min() const {
    if (!left_.empty()) {
      if (!right_.empty()) {
        return std::min(left_.back().second, right_.back().second, Compare());
      }
      return left_.back().second;
    }
    return right_.back().second;
  }
  
  void push(T&& value) {
    std::pair<T, T> p;
    p.second = left_.empty() ? value : std::min(value, left_.back().second, Compare());
    p.first = std::move(value);
    left_.push_back(std::move(p));
  }
  
  void pop() {
    if (right_.empty()) {
      left_.swap(right_);
      reverse(right_.begin(), right_.end());
    }
    right_.pop_back();
  }
  
  void swap(MinQueue<T, Compare>& other) noexcept {
    left_.swap(other.left_);
    right_.swap(other.right_);
  }
};

template<class T, class Compare>
void swap(MinQueue<T, Compare>& left, MinQueue<T, Compare>& right) noexcept {
  left.swap(right);
}
