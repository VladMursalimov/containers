#include "s21_map.h"
namespace s21 {
template <typename T, typename V>
Map<T, V>::Map() : tree_() {}
template <typename T, typename V>
Map<T, V>::Map(
    std::initializer_list<typename Map<T, V>::value_type> const& items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    this->insert(*i);
  }
}
template <typename T, typename V>
Map<T, V>::Map(const Map& m) : tree_(m.get_tree()) {}
template <typename T, typename V>
Map<T, V> Map<T, V>::operator=(Map<T, V>&& m) {
  if (this != &m) {
    tree_ = std::move(m.tree_);
  }
  return *this;
}
template <typename T, typename V>
Map<T, V>::~Map() {}

template <typename T, typename V>
std::pair<typename Map<T, V>::iterator, bool> Map<T, V>::insert(
    const value_type& value) {
  std::pair<typename Map<T, V>::iterator, bool> result;
  if (check_duplicates(value)) {
    auto res = this->tree_.Search(value);
    return std::make_pair(iterator(res), false);
  }
  this->tree_.Insert(value);
  auto res = this->tree_.Search(value);
  if (this->tree_.GetInserted()) {
    result = std::make_pair(iterator(res), true);
  } else {
    result = std::make_pair(iterator(res), false);
  }
  return result;
}
template <typename T, typename V>
std::pair<typename Map<T, V>::iterator, bool> Map<T, V>::insert(
    const key_type& key, const mapped_type& obj) {
  return insert(std::pair<key_type, mapped_type>(key, obj));
}
template <typename T, typename V>
std::pair<typename Map<T, V>::iterator, bool> Map<T, V>::insert_or_assign(
    const key_type& key, const mapped_type& obj) {
  if (this->empty()) {
    return insert(std::make_pair(key, obj));
  } else {
    iterator i = this->begin();
    for (; i != this->end(); ++i) {
      if (i->first == key) {
        i->second = obj;
        return std::make_pair(i, false);
      }
    }
    return insert(std::make_pair(key, obj));
  }
}
template <typename T, typename V>
typename Map<T, V>::mapped_type& Map<T, V>::at(const T& key) {
  return operatorHelper(key, 0);
}
template <typename T, typename V>
typename Map<T, V>::mapped_type& Map<T, V>::operator[](const T& key) {
  return operatorHelper(key, 1);
}
template <typename T, typename V>
typename Map<T, V>::iterator Map<T, V>::begin() {
  Node<value_type, V>* node = tree_.GetRoot();
  if (node == nullptr) {
    return iterator(nullptr);
  }
  while (node->left != nullptr && !node->left->isSentinel) {
    node = node->left;
  }
  if (node->isSentinel) {
    return iterator(nullptr);
  } else {
    return iterator(node);
  }
}
template <typename T, typename V>
typename Map<T, V>::iterator Map<T, V>::end() {
  return iterator(nullptr, tree_.GetRoot());
}
template <typename T, typename V>
bool Map<T, V>::empty() {
  if (this->tree_.GetRoot() == nullptr) {
    return true;
  }
  if (this->tree_.GetRoot()->size_ == 0) {
    return true;
  }
  return false;
}
template <typename T, typename V>
typename Map<T, V>::size_type Map<T, V>::size() {
  if (this->tree_.GetRoot() == nullptr) {
    return 0;
  }
  return tree_.GetRoot()->size_;
}
template <typename T, typename V>
typename Map<T, V>::size_type Map<T, V>::max_size() {
  return allocator.max_size() / 10;
}
template <typename T, typename V>
void Map<T, V>::clear() {
  if (this->get_tree().GetRoot()) {
    for (iterator i = this->begin(); i != this->end(); i++) {
      this->erase(i);
    }
  }
}
template <typename T, typename V>
void Map<T, V>::erase(typename Map<T, V>::iterator pos) {
  if (pos != nullptr) {
    this->tree_.Remove(*pos);
  }
}
template <typename T, typename V>
void Map<T, V>::swap(Map& other) {
  tree_.Swap(other.tree_);
}
template <typename T, typename V>
void Map<T, V>::merge(Map& other) {
  std::pair<typename Map<T, V>::iterator, bool> result;
  iterator iter = other.begin();
  while (iter != other.end()) {
    result = this->insert(*iter);
    if (result.second) other.erase(iter);
    iter++;
  }
}
template <typename T, typename V>
bool Map<T, V>::contains(const T& key) {
  for (iterator i = this->begin(); i != this->end(); i++) {
    if (i->first == key) return true;
  }
  return false;
}
template <typename T, typename V>
typename Map<T, V>::mapped_type& Map<T, V>::operatorHelper(const T& key,
                                                           int flag) {
  iterator i = this->begin();
  if (i != nullptr) {
    for (; i != this->end(); i++) {
      if (i->first == key) {
        return i->second;
      }
    }
    if (flag) {
      auto res = insert(value_type(key, mapped_type()));
      return res.first->second;
    } else {
      throw std::invalid_argument("This key doesn't exist");
    }
  }
  static mapped_type default_value;
  return default_value;
}
template <typename T, typename V>
const AVLTree<typename Map<T, V>::value_type, V>& Map<T, V>::get_tree() const {
  return tree_;
}
template <typename T, typename V>
bool Map<T, V>::check_duplicates(const value_type& value) {
  auto i = this->begin();
  for (; i != this->end(); i++) {
    if (i->first == value.first) {
      return true;
    }
  }
  return false;
}
}  // namespace s21