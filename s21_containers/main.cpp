#include "TreeRB/TreeRB.h"
#include "list/list.h"

int main() {
  s21::TreeRB<int> tree;

  // Inserting elements into the tree
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);
  tree.insert(40);
  tree.insert(50);
  tree.insert(25);
  tree.insert(10);

  // Performing traversals
  std::cout << "Inorder traversal: ";
  tree.inorder();

  std::cout << "Preorder traversal: ";
  tree.preorder();

  std::cout << "Postorder traversal: ";
  tree.postorder();

  // Searching for an element
  int searchKey = 10;
  if (tree.search(searchKey)) {
    std::cout << "Element " << searchKey << " found in the tree." << std::endl;
  } else {
    std::cout << "Element " << searchKey << " not found in the tree."
              << std::endl;
  }

  // Deleting an element
  tree.deleteValue(20);
  std::cout << "Inorder traversal after deletion of 20: ";
  tree.inorder();

  return 0;
}
