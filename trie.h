#include <cstddef>
#include <limits>
#include <vector>

template <class T>
class PrefixTrie {
 private:
  std::vector<std::vector<T>> trie_;
 public:
  PrefixTrie() : trie_(1, std::vector<T>(std::numeric_limits<T>::max())) {}
  
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

template <class T>
class Trie {
 private:
  class Node {
    public:
      std::vector<Node*> children_;
      Node() : children_(std::numeric_limits<T>::max()) {}
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
