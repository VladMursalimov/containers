#include "list.h"

#include <limits>

template <typename T>
List<T>::List() {
  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

template <typename T>
List<T>::List(size_type n) : head_(nullptr), tail_(nullptr) {
  initialize(n);
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const& items)
    : head_(nullptr), tail_(nullptr) {
  for (const auto& item : items) {
    if (head_ == nullptr) {
      head_ = new Node(item);
      tail_ = head_;
    } else {
      tail_->next_ = new Node(item);
      tail_->next_->prev_ = tail_;
      tail_ = tail_->next_;
    }
  }
}

template <typename T>
List<T>::~List() {
  clear();
}

template <typename T>
List<T>::List(const List& l) : head_(nullptr), tail_(nullptr) {
  Node* cur = l.head_;
  while (cur != nullptr) {
    push_back(cur->value_);
    cur = cur->next_;
  }
}

template <typename T>
List<T>::List(List&& l) {
  head_ = l.head_;
  tail_ = l.tail_;
  size_ = l.size_;
  l.size_ = 0;
  l.head_ = nullptr;
  l.tail_ = nullptr;
}

template <typename T>
typename List<T>::List& List<T>::operator=(List&& l) {
  if (this != &l) {
    while (head_ != nullptr) {
      Node* tmp = head_;
      head_ = head_->next_;
      delete tmp;
    }
    head_ = l.head_;
    tail_ = l.tail_;
    size_ = l.size_;
    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
  }
  return *this;
}

template <typename T>
typename List<T>::const_reference List<T>::front() {
  if (head_ == nullptr) {
    throw std::out_of_range("List is empty");
  }
  return head_->value_;
}

template <typename T>
typename List<T>::const_reference List<T>::back() {
  if (tail_ == nullptr) {
    throw std::out_of_range("List is empty");
  }
  return tail_->value_;
}

template <typename T>
void List<T>::initialize(size_type n) {
  size_ = n;
  for (size_type i = 0; i < n; ++i) {
    Node* newNode = new Node(0);
    if (head_ == nullptr) {
      head_ = tail_ = newNode;
    } else {
      tail_->next_ = newNode;
      newNode->prev_ = tail_;
      tail_ = newNode;
    }
  }
}

template <typename T>
void List<T>::printList() {
  Node* i = head_;
  while (i != nullptr) {
    std::cout << i->value_ << " ";
    i = i->next_;
  }
  std::cout << std::endl;
}

template <typename T>
void List<T>::fillList() {
  Node* cur = head_;
  for (value_type i = 0; cur != nullptr; ++i) {
    cur->value_ = i;
    cur = cur->next_;
  }
}

template <typename T>
typename List<T>::iterator List<T>::begin() {
  return iterator(head_);
}

template <typename T>
typename List<T>::iterator List<T>::end() {
  return iterator(nullptr);
}

template <typename T>
typename List<T>::size_type List<T>::size() {
  int c = 0;
  while (head_ != nullptr) {
    head_ = head_->next_;
    c++;
  }
  return c;
}

template <typename T>
bool List<T>::empty() {
  return size_ == 0;
}

template <typename T>
typename List<T>::size_type List<T>::max_size() {
  return (std::numeric_limits<size_type>::max() / sizeof(Node) / 2);
}

template <typename T>
void List<T>::clear() {
  Node* current = head_;
  while (current != nullptr) {
    Node* next = current->next_;
    delete current;
    current = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  Node* newNode = new Node(value);
  Node* current = pos.get_node();

  if (current == nullptr) {
    if (tail_ == nullptr) {
      head_ = tail_ = newNode;
    } else {
      newNode->prev_ = tail_;
      tail_->next_ = newNode;
      tail_ = newNode;
    }
  } else {
    newNode->next_ = current;
    newNode->prev_ = current->prev_;
    if (current->prev_ != nullptr) {
      current->prev_->next_ = newNode;
    } else {
      head_ = newNode;
    }
    current->prev_ = newNode;
  }
  ++size_;
  return iterator(newNode);
}

template <typename T>
void List<T>::erase(iterator pos) {
  Node* current = pos.get_node();
  if (current == nullptr) {
    throw std::out_of_range("Iterator does not point to a valid node");
  }

  if (current == head_) {
    head_ = current->next_;
    if (head_ != nullptr) {
      head_->prev_ = nullptr;
    } else {
      tail_ = nullptr;
    }
  } else if (current == tail_) {
    tail_ = current->prev_;
    if (tail_ != nullptr) {
      tail_->next_ = nullptr;
    } else {
      head_ = nullptr;
    }
  } else {
    current->prev_->next_ = current->next_;
    current->next_->prev_ = current->prev_;
  }

  delete current;
  --size_;
}

template <typename T>
void List<T>::push_back(const_reference value) {
  size_++;
  if (head_ == nullptr) {
    head_ = new Node(value);
    tail_ = head_;
  } else {
    tail_->next_ = new Node(value);
    tail_->next_->prev_ = tail_;
    tail_ = tail_->next_;
  }
}

template <typename T>
void List<T>::pop_back() {
  if (tail_ == nullptr) {
    throw std::out_of_range("List is empty");
  }
  Node* tmp = tail_;
  if (tail_->prev_ != nullptr) {
    tail_ = tail_->prev_;
    tail_->next_ = nullptr;
  } else {
    head_ = tail_ = nullptr;
  }
  delete tmp;
  --size_;
}

template <typename T>
void List<T>::push_front(const_reference value) {
  Node* newNode = new Node(value);
  newNode->next_ = head_;
  if (head_ != nullptr) {
    head_->prev_ = newNode;
  } else {
    tail_ = newNode;
  }
  head_ = newNode;
  size_++;
}

template <typename T>
void List<T>::pop_front() {
  if (head_ == nullptr) {
    throw std::out_of_range("List is empty");
  }
  Node* tmp = head_;
  if (head_->next_ != nullptr) {
    head_ = head_->next_;
    head_->prev_ = nullptr;
  } else {
    head_ = tail_ = nullptr;
  }
  delete tmp;
  --size_;
}

template <typename T>
void List<T>::swap(List& other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename T>
void List<T>::merge(List& other) {
  if (this == &other) {
    throw std::invalid_argument("Cannot merge the list with itself");
  }
  Node* cur = head_;
  Node* other_cur = other.head_;

  while (other_cur != nullptr) {
    Node* tmp = other_cur->next_;
    if (cur == nullptr) {
      push_back(other_cur->value_);
      other_cur = tmp;
      continue;
    }

    while (cur != nullptr && cur->value_ <= other_cur->value_) {
      if (cur->next_ == nullptr || cur->next_->value_ > other_cur->value_) {
        Node* newNode = new Node(other_cur->value_);
        newNode->next_ = cur->next_;
        newNode->prev_ = cur;
        if (cur->next_ != nullptr) {
          cur->next_->prev_ = newNode;
        } else {
          tail_ = newNode;
        }
        cur->next_ = newNode;
        size_++;
        break;
      }
      cur = cur->next_;
    }
    if (cur->value_ > other_cur->value_) {
      this->push_front(other_cur->value_);
    }
    other_cur = tmp;
  }

  // Очистка другого списка
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
void List<T>::splice(const_iterator pos, List& other) {
  
}