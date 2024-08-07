#include "vector/vector.h"

#include <iostream>
#include <stdexcept>
#include <valarray>

namespace s21 {
template <class T>
Vector<T>::Vector() : size_(0), capacity_(0), container_(nullptr) {}

template <class T>
Vector<T>::Vector(size_type n)
    : size_(n), capacity_(n), container_(new value_type[n]) {
  if (max_size() < n) {
    throw std::out_of_range(
        "Cannot create vector: size is larger than max_size");
  }
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> const &items)
    : size_(items.size()), capacity_(items.size()), container_(nullptr) {
  if (size_) {
    container_ = new value_type[size_];
    std::copy(items.begin(), items.end(), container_);
  }
}

template <class T>
Vector<T>::Vector(const Vector &v)
    : size_(v.size_), capacity_(v.capacity_), container_(nullptr) {
  if (v.container_) {
    container_ = new value_type[capacity_];
    for (size_type i = 0; i < size_; i++) {
      container_[i] = v.container_[i];
    }
  }
}

template <class T>
Vector<T>::Vector(Vector &&v)
    : size_(v.size_), capacity_(v.capacity_), container_(v.container_) {
  v.size_ = 0;
  v.capacity_ = 0;
  v.container_ = nullptr;
}

template <class T>
Vector<T>::~Vector() = default;

template <class T>
Vector<T> &Vector<T>::operator=(Vector &&v) {
  if (this != &v) {
    delete[] this->container_;

    size_ = v.size_;
    capacity_ = v.capacity_;
    container_ = v.container_;

    v.size_ = 0;
    v.capacity_ = 0;
    v.container_ = nullptr;
  }
  return *this;
}

template <class T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
  if (pos >= size_ || pos < 0) {
    throw std::out_of_range("Index out of range");
  }
  return container_[pos];
}

template <class T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  return container_[pos];
}

template <class T>
typename Vector<T>::const_reference Vector<T>::front() {
  if (this->empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return *container_;
}

template <class T>
typename Vector<T>::const_reference Vector<T>::back() {
  if (this->empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return *(container_ + size_ - 1);
}

template <class T>
T *Vector<T>::data() {
  return container_;
}

template <class T>
typename Vector<T>::iterator Vector<T>::begin() {
  return iterator(container_);
}

template <class T>
typename Vector<T>::iterator Vector<T>::end() {
  return iterator(container_ + size_);
}

template <class T>
typename Vector<T>::const_iterator Vector<T>::begin() const {
  return iterator(container_);
}

template <class T>
typename Vector<T>::const_iterator Vector<T>::end() const {
  return iterator(container_ + size_);
}

template <class T>
bool Vector<T>::empty() const {
  return size_ == 0;
}

template <class T>
typename Vector<T>::size_type Vector<T>::size() const {
  return size_;
}

template <class T>
typename Vector<T>::size_type Vector<T>::max_size() const {
  char bits = 63;
  if (sizeof(void *) == 4) {
    bits = 31;
  }
  return static_cast<size_type>(std::pow(2, bits)) / sizeof(value_type) - 1;
}

template <class T>
void Vector<T>::reserve(size_type size) {
  if (size >= max_size()) {
    throw std::length_error("Size is larger that max size");
  }
  if (size > size_) {
    this->add_memory(size, true);
  }
}

template <class T>
void Vector<T>::shrink_to_fit() {
  if (capacity_ > size_) {
    value_type *tmp = container_;
    container_ = new value_type[size_];
    for (size_type i = 0; i < size_; i++) {
      container_[i] = std::move(tmp[i]);
    }
    capacity_ = size_;
    delete[] tmp;
  }
}

template <class T>
void Vector<T>::add_memory(size_type size, bool flag) {
  capacity_ = this->add_memory_size(size, flag);
  value_type *tmp = this->container_;
  container_ = new value_type[this->capacity_];
  for (size_t i = 0; i < this->size_; ++i) {
    this->container_[i] = tmp[i];
  }
  delete[] tmp;
}

template <class T>
typename Vector<T>::size_type Vector<T>::add_memory_size(size_type size,
                                                         bool flag) {
  size_type n = 2;
  return flag ? size : n * (capacity_ > 0 ? capacity_ : n);
}

template <class T>
typename Vector<T>::size_type Vector<T>::capacity() const {
  return capacity_;
}

template <class T>
void Vector<T>::clear() {
  for (size_type i = 0; i < size_; i++) {
    container_[i] = 0;
  }
  size_ = 0;
}

template <class T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type cur_pos = &(*pos) - container_;

  if (cur_pos < 0 || cur_pos > size_) {
    throw std::out_of_range("Index out of range");
  }
  if (size_ + 1 > capacity_) {
    size_type new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    add_memory(new_capacity, true);
  }
  for (size_type i = size_; i > cur_pos; --i) {
    container_[i] = container_[i - 1];
  }
  container_[cur_pos] = value;
  size_++;
  return iterator(container_ + cur_pos);
}

template <class T>
void Vector<T>::erase(iterator pos) {
  size_type cur_pos = &(*pos) - container_;
  if (cur_pos < 0 || cur_pos > size_) {
    throw std::out_of_range("Erase error: Index out of range");
  }
  if (pos == end() - 1) {
    container_[cur_pos].~T();
  } else {
    for (size_type i = cur_pos; i < size_; i++) {
      container_[i] = std::move(container_[i + 1]);
    }
    container_[size_ - 1].~T();
  }
  size_--;
}
template <class T>
void Vector<T>::push_back(const_reference value) {
  if (size_ + 1 > capacity_) {
    size_type new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    add_memory(new_capacity, true);
  }
  container_[size_] = value;  // Storing value at the current size index
  size_++;
}
template <class T>
void Vector<T>::pop_back() {
  if (size_ > 0) {
    container_[size_ - 1].~T();
    size_--;
  }
}
template <class T>
void Vector<T>::swap(Vector &other) {
  std::swap(other.size_, size_);
  std::swap(other.capacity_, capacity_);
  std::swap(other.container_, container_);
}

template <class T>
void Vector<T>::print_vector() {
  for (size_type i = 0; i < size_; i++) {
    std::cout << container_[i] << " ";
  }
  std::cout << std::endl;
}

}  // namespace s21