#ifndef VECTOR_H
#define VECTOR_H
#include <initializer_list>

namespace s21 {
template <class T>
class VectorIterator;

template <class T>
class VectorConstIterator;

template <class T>
class Vector {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = VectorIterator<T>;
  using const_iterator = VectorConstIterator<T>;
  using size_type = std::size_t;
  using pointer = T *;

  // Vector Member functions
  Vector();
  Vector(size_type n);
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v);
  ~Vector();
  Vector &operator=(Vector &&v);

  // Vector Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T *data();

  // Vector Iterators
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // Vector Capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  size_type capacity() const;
  void reserve(size_type size);
  void shrink_to_fit();

  // Vector Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector &other);

  void print_vector();

 private:
  size_type size_;
  size_type capacity_;
  value_type *container_;

  void add_memory(size_type size, bool flag);
  size_type add_memory_size(size_type size, bool flag);
};

template <class T>
class VectorIterator {
 public:
  using value_type = T;
  using pointer = T *;
  using reference = T &;

  VectorIterator() : ptr_(nullptr) {}
  explicit VectorIterator(pointer ptr) : ptr_(ptr) {}

  reference operator*() const { return *ptr_; }
  pointer operator->() const { return ptr_; }

  VectorIterator &operator++() {
    ++ptr_;
    return *this;
  }

  VectorIterator &operator--() {
    --ptr_;
    return *this;
  }

  VectorIterator operator++(int) {
    VectorIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  VectorIterator operator--(int) {
    VectorIterator tmp = *this;
    --(*this);
    return tmp;
  }

  VectorIterator operator+(const std::size_t value) const {
    return VectorIterator(ptr_ + value);
  }

  VectorIterator operator-(const std::size_t value) const {
    return VectorIterator(ptr_ - value);
  }

  bool operator==(const VectorIterator &other) const {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const VectorIterator &other) const {
    return ptr_ != other.ptr_;
  }

  operator VectorConstIterator<T>() const {
    return VectorConstIterator<T>(ptr_);
  }

 private:
  pointer ptr_;
};

template <class T>
class VectorConstIterator {
  friend class Vector<T>;
  friend class VectorIterator<T>;

  using value_type = T;
  using pointer = T *;
  using reference = T &;

 public:
  VectorConstIterator() { ptr_ = nullptr; };
  VectorConstIterator(pointer ptr) { ptr_ = ptr; };
  value_type operator*() const { return (*ptr_); }
  pointer operator->() { return ptr_; }

  VectorConstIterator &operator++() {
    ptr_++;
    return *this;
  }

  VectorConstIterator &operator--() {
    ptr_--;
    return *this;
  }

  VectorConstIterator operator++(int) {
    VectorConstIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  VectorConstIterator operator--(int) {
    VectorConstIterator tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const VectorConstIterator &other) {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const VectorConstIterator &other) {
    return ptr_ != other.ptr_;
  }

  operator VectorIterator<T>() const { return VectorIterator<T>(ptr_); }

 private:
  pointer ptr_;
};
template class Vector<int>;
template class Vector<double>;
template class Vector<char>;
template class Vector<float>;

}  // namespace s21

#endif  // VECTOR_H
