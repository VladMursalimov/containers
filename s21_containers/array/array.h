#ifndef ARRAY_H
#define ARRAY_H
#include <algorithm>
#include <stdexcept>
namespace s21 {
template <class T>
class ArrayIterator;

template <class T>
class ArrayConstIterator;

template <class T>
class Array {
 public:
  using value_type = T;
  using size_type = size_t;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;

 private:
  T* data;
  size_type size_;

 public:
  // Конструкторы, деструктор и оператор присваивания
  Array() : data(nullptr), size_(0) {}

  Array(std::initializer_list<value_type> const& items) : size_(items.size()) {
    data = new T[size_];
    std::copy(items.begin(), items.end(), data);
  }

  Array(size_type size) : size_(size) { data = new T[size_]; }

  Array(const Array& other) : size_(other.size_) {
    data = new T[size_];
    std::copy(other.begin(), other.end(), data);
  }

  Array& operator=(const Array& other) {
    if (this == &other) return *this;

    delete[] data;
    size_ = other.size_;
    data = new T[size_];
    std::copy(other.begin(), other.end(), data);
    return *this;
  }

  ~Array() { delete[] data; }

  // Array Element access
  reference at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("Index out of range");
    return data[pos];
  }

  reference operator[](size_type pos) { return data[pos]; }

  const_reference operator[](size_type pos) const { return data[pos]; }

  const_reference front() const {
    if (empty()) throw std::out_of_range("Array is empty");
    return data[0];
  }

  const_reference back() const {
    if (empty()) throw std::out_of_range("Array is empty");
    return data[size_ - 1];
  }

  iterator data_ptr() { return data; }

  // Array Iterators
  iterator begin() { return data; }

  iterator end() { return data + size_; }

  const_iterator begin() const { return data; }

  const_iterator end() const { return data + size_; }

  // Array Capacity
  bool empty() const { return size_ == 0; }

  size_type size() const { return size_; }

  size_type max_size() const { return static_cast<size_type>(-1) / sizeof(T); }

  // Array Modifiers
  void swap(Array& other) {
    std::swap(data, other.data);
    std::swap(size_, other.size_);
  }

  void fill(const_reference value) { std::fill(begin(), end(), value); }

  // Изменение размера массива
  void resize(size_type newSize) {
    T* newData = new T[newSize];
    size_type minSize = (newSize < size_) ? newSize : size_;
    std::copy(data, data + minSize, newData);
    delete[] data;
    data = newData;
    size_ = newSize;
  }
};
template class Array<int>;
template class Array<double>;
template class Array<char>;
template class Array<float>;
}  // namespace s21
#endif  // ARRAY_H
