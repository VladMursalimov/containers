#include "TreeRB.h"

#include <fstream>
#include <iostream>

namespace s21 {
template <class T>
void TreeRB<T>::leftRotate(Node*& root, Node*& pt) {
  Node* pt_right = pt->right;

  pt->right = pt_right->left;

  if (pt->right != nullptr) pt->right->parent = pt;

  pt_right->parent = pt->parent;

  if (pt->parent == nullptr)
    root = pt_right;
  else if (pt == pt->parent->left)
    pt->parent->left = pt_right;
  else
    pt->parent->right = pt_right;

  pt_right->left = pt;
  pt->parent = pt_right;
}

template <class T>
void TreeRB<T>::rightRotate(Node*& root, Node*& pt) {
  Node* pt_left = pt->left;

  pt->left = pt_left->right;

  if (pt->left != nullptr) pt->left->parent = pt;

  pt_left->parent = pt->parent;

  if (pt->parent == nullptr)
    root = pt_left;
  else if (pt == pt->parent->left)
    pt->parent->left = pt_left;
  else
    pt->parent->right = pt_left;

  pt_left->right = pt;
  pt->parent = pt_left;
}

template <class T>
void TreeRB<T>::insertFixUp(Node*& root, Node*& pt) {
  Node* parent_pt = nullptr;
  Node* grand_parent_pt = nullptr;

  while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
    parent_pt = pt->parent;
    grand_parent_pt = pt->parent->parent;

    if (parent_pt == grand_parent_pt->left) {
      Node* uncle_pt = grand_parent_pt->right;

      if (uncle_pt != nullptr && uncle_pt->color == RED) {
        grand_parent_pt->color = RED;
        parent_pt->color = BLACK;
        uncle_pt->color = BLACK;
        pt = grand_parent_pt;
      } else {
        if (pt == parent_pt->right) {
          leftRotate(root, parent_pt);
          pt = parent_pt;
          parent_pt = pt->parent;
        }

        rightRotate(root, grand_parent_pt);
        std::swap(parent_pt->color, grand_parent_pt->color);
        pt = parent_pt;
      }
    } else {
      Node* uncle_pt = grand_parent_pt->left;

      if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
        grand_parent_pt->color = RED;
        parent_pt->color = BLACK;
        uncle_pt->color = BLACK;
        pt = grand_parent_pt;
      } else {
        if (pt == parent_pt->left) {
          rightRotate(root, parent_pt);
          pt = parent_pt;
          parent_pt = pt->parent;
        }

        leftRotate(root, grand_parent_pt);
        std::swap(parent_pt->color, grand_parent_pt->color);
        pt = parent_pt;
      }
    }
  }

  root->color = BLACK;
}

template <class T>
void TreeRB<T>::insert(int data) {
  Node* pt = new Node(data);
  Node* parent = nullptr;
  Node* current = root;

  while (current != nullptr) {
    parent = current;
    if (pt->data < current->data)
      current = current->left;
    else
      current = current->right;
  }

  pt->parent = parent;

  if (parent == nullptr)
    root = pt;
  else if (pt->data < parent->data)
    parent->left = pt;
  else
    parent->right = pt;

  insertFixUp(root, pt);
}

template <class T>
typename TreeRB<T>::Node* TreeRB<T>::search(Node* root, int data) {
  if (root == nullptr || root->data == data) return root;

  if (data < root->data) return search(root->left, data);

  return search(root->right, data);
}

template <class T>
typename TreeRB<T>::Node* TreeRB<T>::minimum(Node* node) {
  while (node->left != nullptr) node = node->left;
  return node;
}

template <class T>
void TreeRB<T>::deleteFixUp(Node*& root, Node*& x) {
  while (x != root && x->color == BLACK) {
    if (x == x->parent->left) {
      Node* w = x->parent->right;

      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        leftRotate(root, x->parent);
        w = x->parent->right;
      }

      if (w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          rightRotate(root, w);
          w = x->parent->right;
        }

        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        leftRotate(root, x->parent);
        x = root;
      }
    } else {
      Node* w = x->parent->left;

      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rightRotate(root, x->parent);
        w = x->parent->left;
      }

      if (w->right->color == BLACK && w->left->color == BLACK) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          leftRotate(root, w);
          w = x->parent->left;
        }

        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        rightRotate(root, x->parent);
        x = root;
      }
    }
  }

  x->color = BLACK;
}

template <class T>
void TreeRB<T>::deleteNode(Node*& root, Node*& z) {
  Node* y = z;
  Node* x;
  Color originalColor = y->color;

  if (z->left == nullptr) {
    x = z->right;
    if (x) x->parent = z->parent;
    if (z->parent == nullptr)
      root = x;
    else if (z == z->parent->left)
      z->parent->left = x;
    else
      z->parent->right = x;
  } else if (z->right == nullptr) {
    x = z->left;
    if (x) x->parent = z->parent;
    if (z->parent == nullptr)
      root = x;
    else if (z == z->parent->left)
      z->parent->left = x;
    else
      z->parent->right = x;
  } else {
    y = minimum(z->right);
    originalColor = y->color;
    x = y->right;
    if (y->parent == z) {
      if (x) x->parent = y;
    } else {
      if (x) x->parent = y->parent;
      y->parent->left = x;
      y->right = z->right;
      y->right->parent = y;
    }

    if (z->parent == nullptr)
      root = y;
    else if (z == z->parent->left)
      z->parent->left = y;
    else
      z->parent->right = y;

    y->parent = z->parent;
    y->color = z->color;
    y->left = z->left;
    y->left->parent = y;
  }

  delete z;

  if (originalColor == BLACK) deleteFixUp(root, x);
}

template <class T>
void TreeRB<T>::inorderTraversal(Node* root) {
  if (root == nullptr) return;

  inorderTraversal(root->left);
  std::cout << root->data << " ";
  inorderTraversal(root->right);
}

template <class T>
void TreeRB<T>::preorderTraversal(Node* root) {
  if (root == nullptr) return;

  std::cout << root->data << " ";
  preorderTraversal(root->left);
  preorderTraversal(root->right);
}

template <class T>
void TreeRB<T>::postorderTraversal(Node* root) {
  if (root == nullptr) return;

  postorderTraversal(root->left);
  postorderTraversal(root->right);
  std::cout << root->data << " ";
}

template <class T>
void TreeRB<T>::deleteValue(int data) {
  Node* node_to_delete = search(root, data);
  if (node_to_delete != nullptr) {
    deleteNode(root, node_to_delete);
  }
}

template <class T>
bool TreeRB<T>::search(int data) { return search(root, data) != nullptr; }

template <class T>
void TreeRB<T>::inorder() {
  inorderTraversal(root);
  std::cout << std::endl;
}

template <class T>
void TreeRB<T>::preorder() {
  preorderTraversal(root);
  std::cout << std::endl;
}

template <class T>
void TreeRB<T>::postorder() {
  postorderTraversal(root);
  std::cout << std::endl;
}

}  // namespace s21
