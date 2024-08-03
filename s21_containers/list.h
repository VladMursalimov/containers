#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <iostream>

template <typename T>
class List {
 public:
  /// List Member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  /// List Functions
  List();             // Default constructor
  List(size_type n);  // Parameterized constructor
  List(std::initializer_list<value_type> const&
           items);      // Initializer list constructor
  ~List();              // Destructor
  List(const List& l);  // copy constructor
  List(List&& l);       // move constructor
  List& operator=(List&& l);

  /// List Element access
  const_reference front();
  const_reference back();

  /// List Capacity
  bool empty();          // checks whether the container is empty
  size_type size();      // returns the number of elements
  size_type max_size();  // returns the maximum possible number of elements

  /// Helpers
  void initialize(size_type n);
  void printList();  // Function to print the list
  void fillList();   // Fills the list with nums from 0 to n

 private:
  struct Node {
    value_type value_;
    Node* prev_;
    Node* next_;

    Node(value_type value) : value_(value), prev_(nullptr), next_(nullptr) {}
  };

  Node* head_;
  Node* tail_;
  size_type size_;

 public:
  template <typename value_type>
  class ListIterator {
  private:
    Node* current;

  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    ListIterator() : current(nullptr) {}

    ListIterator(Node* node) : current(node) {}

    reference operator*() const {
      return current->value_;
    }

    pointer operator->() const {
      return &(current->value_);
    }

    ListIterator& operator++() {
      current = current->next_;
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator temp = *this;
      ++(*this);
      return temp;
    }

    ListIterator& operator--() {
      current = current->prev_;
      return *this;
    }

    ListIterator operator--(int) {
      ListIterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const ListIterator& other) const {
      return current == other.current;
    }

    bool operator!=(const ListIterator& other) const {
      return current != other.current;
    }

    Node* get_node() const {
      return current;
    }
  };

  template <typename value_type>
  class ListConstIterator : public ListIterator<T> {
   public:
    ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
    const T& operator*() { return ListIterator<T>::operator*(); }
  };


  /// List Iterators
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;


  /// List Modifiers
  void clear();  // Очищает содержимое списка
  iterator insert(iterator pos, const T& value);
  // Вставляет элемент в указанную позицию и возвращает итератор, указывающий на
  // новый элемент
  void erase(iterator pos);         // Удаляет элемент по указанной позиции
  void push_back(const T& value);   // Добавляет элемент в конец списка
  void pop_back();                  // Удаляет последний элемент списка
  void push_front(const T& value);  // Добавляет элемент в начало списка
  void pop_front();                 // Удаляет первый элемент списка
  void swap(List& other);   // Обменивает содержимое списка с другим списком
  void merge(List& other);  // Объединяет два отсортированных списка
  void splice(const_iterator pos, List& other);  // Переносит элементы из списка
                                                 // other, начиная с позиции pos
  void reverse();  // Изменяет порядок элементов списка на обратный
  void unique();   // Удаляет последовательные повторяющиеся элементы
  void sort();     // Сортирует элементы списка
  void quickSort(Node* low, Node* high);
  Node* partition(Node* low, Node* high);
};

template class List<int>;     // Example instantiation
template class List<double>;  // Example instantiation

#endif
