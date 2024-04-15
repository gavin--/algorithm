#include <array>
#include <cstddef>
#include <limits>
#include <vector>

template <class T>
class PrefixTrie {
 private:
  std::vector<std::array<std::size_t, std::numeric_limits<T>::max() + 1>> trie_;
 public:
  PrefixTrie() : trie_(1) {}
  
  void Insert(const std::basic_string<T>& key) {
    for (std::size_t i = 0, t = 0; i <= key.size(); ++i) {
      if (trie_[t][key[i]] == 0) {
        trie_[t][key[i]] = trie_.size();
        trie_.push_back({});
      }
      t = trie_[t][key[i]];
    }
  }
  
  bool Find(const std::basic_string<T>& key) {
    for (std::size_t i = 0, t = 0; i <= key.size(); ++i) {
      if (trie_[t][key[i]] == 0) {
        return false;
      }
      t = trie_[t][key[i]];
    }
    return true;
  }
  
  bool StartsWith(const std::basic_string<T>& key) {
    for (std::size_t i = 0, t = 0; i < key.size(); ++i) {
      if (trie_[t][key[i]] == 0) {
        return false;
      }
      t = trie_[t][key[i]];
    }
    return true;
  }
};

template <class T>
class Trie {
 private:
  class Node {
   public:
    std::array<Node*, std::numeric_limits<T>::max() + 1> children_;
  };
  Node* const root_ = new Node();
 public:
  void Insert(const std::basic_string<T>& key) {
    Node* node = root_;
    for (std::size_t i = 0; i <= key.size(); ++i) {
      if (node->children_[key[i]] == nullptr) {
        node->children_[key[i]] = new Node();
      }
      node = node->children_[key[i]];
    }
  }
  
  void Delete(const std::basic_string<T>& key) {
    Node* node = root_;
    for (std::size_t i = 0; i < key.size(); ++i) {
      if (node->children_[key[i]] == nullptr) {
        return;
      }
      node = node->children_[key[i]];
    }
    if (node->children_[key[key.size()]] == nullptr) {
      return;
    }
    delete node->children_[key[key.size()]];
    node->children_[key[key.size()]] = nullptr;
  }
  
  bool Find(const std::basic_string<T>& key) {
    Node* node = root_;
    for (std::size_t i = 0; i <= key.size(); ++i) {
      if (node->children_[key[i]] == nullptr) {
        return false;
      }
      node = node->children_[key[i]];
    }
    return true;
  }
};
