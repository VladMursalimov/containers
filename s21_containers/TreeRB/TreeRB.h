#ifndef TREERB_H
#define TREERB_H
namespace s21 {
template <typename T>
class TreeRB {
private:
  enum Color { RED, BLACK };

  struct Node {
    T data;
    Color color;
    Node *left, *right, *parent;

    Node(T data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
  };

  Node* root;

  // Utility functions
  void leftRotate(Node*& root, Node*& pt);
  void rightRotate(Node*& root, Node*& pt);
  void insertFixUp(Node*& root, Node*& pt);
  void deleteFixUp(Node*& root, Node*& x);
  void deleteNode(Node*& root, Node*& z);
  Node* search(Node* root, int data);
  Node* minimum(Node* node);
  void inorderTraversal(Node* root);
  void preorderTraversal(Node* root);
  void postorderTraversal(Node* root);

public:
  TreeRB() : root(nullptr) {}

  void insert(int data);
  void deleteValue(int data);
  bool search(int data);
  void inorder();
  void preorder();
  void postorder();
};

template class TreeRB<int>;
template class TreeRB<double>;
template class TreeRB<char>;
template class TreeRB<float>;
}  // namespace s21
#endif  // TREERB_H
