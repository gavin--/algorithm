#include <cstddef>
#include <map>
#include <string_view>
#include <vector>

template <class T>
class PrefixTrie {
 public:
  PrefixTrie() : trie_(1) {}

  void Insert(std::basic_string_view<T> key) {
    for (std::size_t i = 0, t = 0; i <= key.size(); ++i) {
      auto& child_node = trie_[t][key[i]];
      if (child_node == 0) {
        child_node = trie_.size();
        trie_.push_back({});
      }
      t = child_node;
    }
  }

  bool Find(std::basic_string_view<T> key) const {
    for (std::size_t i = 0, t = 0; i <= key.size(); ++i) {
      auto it = trie_[t].find(key[i]);
      if (it == trie_[t].end()) {
        return false;
      }
      t = it->second;
    }
    return true;
  }

  bool StartsWith(std::basic_string_view<T> key) const {
    for (std::size_t i = 0, t = 0; i < key.size(); ++i) {
      auto it = trie_[t].find(key[i]);
      if (it == trie_[t].end()) {
        return false;
      }
      t = it->second;
    }
    return true;
  }

 private:
  std::vector<std::map<T, std::size_t>> trie_;
};

template <class T>
class Trie {
 public:
  void Insert(std::basic_string_view<T> key) {
    Node* node = root_;
    for (std::size_t i = 0; i <= key.size(); ++i) {
      auto& child_node = node->children_[key[i]];
      if (child_node == nullptr) {
        child_node = new Node();
      }
      node = child_node;
    }
  }

  void Delete(std::basic_string_view<T> key) {
    Node* node = root_;
    for (std::size_t i = 0; i < key.size(); ++i) {
      if (auto it = node->children_.find(key[i]); it == node->children_.end()) {
        return;
      } else {
        node = it->second;
      }
    }
    if (auto it = node->children_.find(key[key.size()]);
        it == node->children_.end()) {
      return;
    } else {
      delete it->second;
      node->children_.erase(it);
    }
  }

  bool Find(std::basic_string_view<T> key) const {
    Node* node = root_;
    for (std::size_t i = 0; i <= key.size(); ++i) {
      if (auto it = node->children_.find(key[i]); it == node->children_.end()) {
        return false;
      } else {
        node = it->second;
      }
    }
    return true;
  }

 private:
  class Node {
   public:
    std::map<T, Node*> children_;
  };
  Node* const root_ = new Node();
};
