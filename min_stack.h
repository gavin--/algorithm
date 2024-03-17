#include <functional>
#include <stack>
#include <utility>

template<class T, class Compare = std::less<T>>
class MinStack {
  protected:
   std::stack<std::pair<T, T>> stack_;
  public:
    auto empty() const {
      return stack_.empty();
    }
    
    auto size() const {
      return stack_.size();
    }
    
    auto top() {
      return stack_.top().first;
    }
    
    auto min() {
      return stack_.top().second;
    }
    
    void push(T&& value) {
      if (stack_.empty()) {
        stack_.push(std::make_pair(value, value));
      } else {
        stack_.push(std::make_pair(value, std::min(value, stack_.top().second, Compare())));
      }
    }
    
    void pop() {
      stack_.pop();
    }
    
    void swap(MinStack<T, Compare>& other) noexcept {
      using std::swap;
      swap(stack_, other.stack_);
    }
};

template<class T, class Compare>
bool operator==(const MinStack<T, Compare>& left, const MinStack<T, Compare>& right) {
  return left.stack_ == right.stack_;
}

template<class T, class Compare>
bool operator!=(const MinStack<T, Compare>& left, const MinStack<T, Compare>& right) {
  return !(left == right);
}

template<class T, class Compare>
bool operator<(const MinStack<T, Compare>& left, const MinStack<T, Compare>& right) {
  return left.stack_ < right.stack_;
}

template<class T, class Compare>
bool operator>(const MinStack<T, Compare>& left, const MinStack<T, Compare>& right) {
  return right < left;
}

template<class T, class Compare>
bool operator<=(const MinStack<T, Compare>& left, const MinStack<T, Compare>& right) {
  return !(right < left);
}

template<class T, class Compare>
bool operator>=(const MinStack<T, Compare>& left, const MinStack<T, Compare>& right) {
  return !(left < right);
}
