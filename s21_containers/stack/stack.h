#ifndef STACK_H
#define STACK_H
#include "list/list.h"
namespace s21 {
template <typename T, typename Container = s21::List<T>>
class Stack {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

 protected:
  Container cont;

 public:
  Stack() : cont() {}
  Stack(std::initializer_list<value_type> const &items) : cont(items) {}
  Stack(const Stack &q) : cont(q.cont) {}
  Stack(Stack &&q) noexcept : cont(std::move(q.cont)) {}
  ~Stack(){};
  Stack &operator=(Stack &&q) noexcept {
    this->cont = std::move(q.cont);
    return *this;
  }

  const_reference top() { return cont.back(); }

  bool empty() { return cont.empty(); }
  size_type size() { return cont.size(); }

  void push(const_reference value) { this->cont.push_back(value); }
  void pop() { this->cont.pop_back(); }
  void swap(Stack &other) noexcept { this->cont.swap(other.cont); }
};

template class Stack<int>;
template class Stack<double>;
template class Stack<char>;
template class Stack<float>;
}  // namespace s21
#endif  // STACK_H
