#ifndef QUEUE_H
#define QUEUE_H

#include "list/list.h"
namespace s21 {
template <typename T, typename Container = s21::List<T>>
class Queue {
public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

 protected:
  Container cont;

 public:
  Queue() : cont() {}
  Queue(std::initializer_list<value_type> const &items) : cont(items) {}
  Queue(const Queue &q) : cont(q.cont) {}
  Queue(Queue &&q) noexcept : cont(std::move(q.cont)) {}
  ~Queue(){};
  Queue &operator=(Queue &&q) noexcept {
    this->cont = std::move(q.cont);
    return *this;
  }

  const_reference front() { return cont.front(); }
  const_reference back() { return cont.back(); }

  bool empty() { return cont.empty(); }
  size_type size() { return cont.size(); }

  void push(const_reference value) { this->cont.push_back(value); }
  void pop() { this->cont.pop_front(); }
  void swap(Queue &other) noexcept { this->cont.swap(other.cont); }
};

template class Queue<int>;
template class Queue<double>;
template class Queue<char>;
template class Queue<float>;
}  // namespace s21

#endif  // QUEUE_H
