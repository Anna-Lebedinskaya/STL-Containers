#ifndef CPP2_S21_CONTAINERS_SRC_S21_STACK_H_
#define CPP2_S21_CONTAINERS_SRC_S21_STACK_H_

#include <iostream>

#include "s21_list.h"

namespace s21 {
template <typename T, typename Container = s21::list<T>>
class stack {
 public:
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  // using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  // stack-Member-functions--------------------------------------------------------

  stack() {}

  stack(std::initializer_list<value_type> const &items) : container(items) {}

  stack(const stack &other) : container(other.container) {}

  stack(stack &&other) : container(other.container) { other.container.clear(); }

  ~stack() {}

  stack<T, Container> &operator=(stack &&other) {
    container.swap(other.container);
    return *this;
  }

  // stack-Element-access----------------------------------------------------------

  const_reference top() const { return container.back(); }

  // stack-Capacity----------------------------------------------------------------

  bool empty() const { return container.empty(); }

  size_type size() const { return container.size(); }

  // stack-Modifiers--------------------------------------------------------------

  void push(const_reference value) { container.push_back(value); }

  void pop() { container.pop_back(); }

  void swap(stack &other) { std::swap(container, other.container); }

  //доп
  template <typename... Args>
  void emplace_front(Args &&... args) {
    container.emplace_back(args...);
  }

 private:
  Container container;
};

}  // namespace s21

#endif
