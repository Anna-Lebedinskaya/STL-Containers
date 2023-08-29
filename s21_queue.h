#ifndef CPP2_S21_CONTAINERS_SRC_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_QUEUE_H_

#include <iostream>
// #include <limits>
// #include <list>

#include "s21_list.h"

namespace s21 {
template <typename T, typename Container = s21::list<T>>
class queue {
 public:
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  // using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  // queue()-Member-functions--------------------------------------------------------

  queue() {}

  queue(std::initializer_list<value_type> const &items) : container(items) {}

  queue(const queue &other) : container(other.container) {}

  queue(queue &&other) : container(other.container) { other.container.clear(); }

  ~queue() {}

  queue<T, Container> &operator=(queue &&other) {
    container.swap(other.container);
    return *this;
  }

  // queue-Element-access----------------------------------------------------------

  const_reference front() const { return container.front(); }

  const_reference back() const { return container.back(); }

  // queue-Capacity----------------------------------------------------------------

  bool empty() const { return container.empty(); }

  size_type size() const { return container.size(); }

  // queue-Modifiers--------------------------------------------------------------

  void push(const_reference value) { container.push_back(value); }

  void pop() { container.pop_front(); }

  void swap(queue &other) { std::swap(container, other.container); }

  //доп
  template <typename... Args>
  void emplace_back(Args &&... args) {
    container.emplace_back(args...);
  }

 private:
  Container container;
};

}  // namespace s21

#endif
