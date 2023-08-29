#ifndef CPP2_S21_CONTAINERS_SRC_S21_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_S21_LIST_H_

#include <iostream>
#include <limits>
#include <vector>

namespace s21 {

template <typename T>
struct Node_list {
  Node_list<T> *prev;
  Node_list<T> *next;
  T value;
  Node_list<T>() : prev(nullptr), next(nullptr), value(0){};
  Node_list<T>(Node_list<T> *prev_init, Node_list<T> *next_init, T value_init)
      : prev(prev_init), next(next_init), value(value_init) {}
};

template <typename T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  class ListIterator {
   public:
    Node_list<value_type> *curr;
    ListIterator(Node_list<value_type> *curr_init);
    iterator &operator++();
    iterator &operator--();
    reference operator*() const;
    bool operator==(const iterator &other) const noexcept;
    bool operator!=(const iterator &other) const noexcept;
  };

  class ListConstIterator : public ListIterator {
   public:
    explicit ListConstIterator(Node_list<value_type> *curr_init = nullptr)
        : ListIterator(curr_init) {}
    ListConstIterator(const ListIterator &other);
    const_reference operator*() const;
  };

  list();
  explicit list(size_type size);
  list(std::initializer_list<value_type> const &items);
  list(const list &other);
  list(list &&other);
  ~list();
  list<value_type> &operator=(list &&other);

  const_reference front() const;
  const_reference back() const;

  iterator begin();
  iterator end();

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  //допы
  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&... args);
  template <typename... Args>
  void emplace_back(Args &&... args);
  template <typename... Args>
  void emplace_front(Args &&... args);

 private:
  Node_list<T> *head_;
  Node_list<T> *tail_;
  size_t size_;
};

}  // namespace s21

#include "s21_list.inl"

#endif