#include "TreeRB/TreeRB.h"

#ifndef SET_H
#define SET_H
namespace s21 {
template <typename T>
class Set {
 private:
  TreeRB<T> tree;  // TreeRB class is assumed to be templated for generic types

 public:
  Set() = default;

  // Inserts an element into the set
  void insert(const T& value) { tree.insert(value); }

  // Removes an element from the set
  void erase(const T& value) { tree.deleteValue(value); }

  // Checks if the set contains the element
  bool contains(const T& value) const { return tree.search(value); }

  // Inorder traversal of the set (sorted order)
  void inorder() const { tree.inorder(); }

  // Preorder traversal of the set
  void preorder() const { tree.preorder(); }

  // Postorder traversal of the set
  void postorder() const { tree.postorder(); }

  // Additional utility functions can be added as needed
};
}  // namespace s21

#endif  // SET_H
