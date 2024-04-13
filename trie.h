#include <cstddef>
#include <limits>
#include <vector>

template <class T>
class PrefixTrie {
 private:
  std::vector<std::vector<T>> trie_;
 public:
  PrefixTrie() {
    trie_.emplace_back(std::numeric_limits<T>::max());
  }
  
  void Insert(const std::basic_string<T>& key) {
    T t = 0;
    for (std::size_t i = 0; i <= key.size(); ++i) {
      if (trie_[t][key[i]] == 0) {
        trie_[t][key[i]] = trie_.size();
        trie_.emplace_back(std::numeric_limits<T>::max());
      }
      t = trie_[t][key[i]];
    }
  }
  
  bool Find(const std::basic_string<T>& key) {
    T t = 0;
    for (std::size_t i = 0; i <= key.size(); ++i) {
      if (trie_[t][key[i]] == 0) {
        return false;
      }
      t = trie_[t][key[i]];
    }
    return true;
  }
  
  bool StartsWith(const std::basic_string<T>& key) {
    T t = 0;
    for (std::size_t i = 0; i < key.size(); ++i) {
      if (trie_[t][key[i]] == 0) {
        return false;
      }
      t = trie_[t][key[i]];
    }
    return true;
  }
};
