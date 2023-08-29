#include "s21_list.h"

// ListIterator----------------------------------------------------------------

template <typename value_type>
s21::list<value_type>::ListIterator::ListIterator(
    Node_list<value_type> *curr_init)
    : curr(curr_init) {}

template <typename value_type>
typename s21::list<value_type>::iterator &
s21::list<value_type>::ListIterator::operator++() {
  curr = (curr) ? curr->next : nullptr;
  return *this;
}

template <typename value_type>
typename s21::list<value_type>::iterator &
s21::list<value_type>::ListIterator::operator--() {
  curr = (curr) ? curr->prev : nullptr;
  return *this;
}

template <typename value_type>
typename s21::list<value_type>::reference
s21::list<value_type>::ListIterator::operator*() const {
  return curr->value;
}

template <typename value_type>
bool s21::list<value_type>::ListIterator::operator==(
    const ListIterator &other) const noexcept {
  return curr == other.curr;
}

template <typename value_type>
bool s21::list<value_type>::ListIterator::operator!=(
    const ListIterator &other) const noexcept {
  return curr != other.curr;
}

// ListConstIterator-----------------------------------------------------------

template <typename value_type>
s21::list<value_type>::ListConstIterator::ListConstIterator(
    const ListIterator &other)
    : ListConstIterator() {
  this->curr = other.curr;
}

template <typename value_type>
typename s21::list<value_type>::const_reference
s21::list<value_type>::ListConstIterator::operator*() const {
  return this->curr->value;
}

// List Functions---------------------------------------------------------------

template <typename value_type>
s21::list<value_type>::list() : size_(0) {
  head_ = new Node_list<value_type>(nullptr, nullptr, 0);
  tail_ = head_;
}

template <typename value_type>
s21::list<value_type>::list(size_type size) : list() {
  for (size_type i = 0; i < size; i++) {
    push_back(0);
  }
}

template <typename value_type>
s21::list<value_type>::list(std::initializer_list<value_type> const &items)
    : list() {
  for (auto it = items.begin(); it != items.end(); it++) {
    push_back(*it);
  }
}

template <typename value_type>
s21::list<value_type>::list(const list &other) : list() {
  Node_list<value_type> *tmp = other.head_;
  for (size_type i = 0; i < other.size_; i++) {
    push_back(tmp->value);
    tmp = tmp->next;
  }
}

template <typename value_type>
s21::list<value_type>::list(list &&other)
    : head_(other.head_), tail_(other.tail_), size_(other.size_) {
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename value_type>
s21::list<value_type>::~list() {
  clear();
  delete head_;
}

template <typename value_type>
s21::list<value_type> &s21::list<value_type>::operator=(list &&other) {
  if (this != &other) {
    clear();
    size_ = other.size_;
    head_ = other.head_;
    other.head_ = nullptr;
    tail_ = other.tail_;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  return *this;
}

// List Element access----------------------------------------------------------

template <typename value_type>
typename s21::list<value_type>::const_reference s21::list<value_type>::front()
    const {
  if (size_ == 0) std::runtime_error("The List is empty");
  return head_->value;
}

template <typename value_type>
typename s21::list<value_type>::const_reference s21::list<value_type>::back()
    const {
  if (size_ == 0) std::runtime_error("The List is empty");
  return tail_->value;
}

// List Iterators---------------------------------------------------------------

template <typename value_type>
typename s21::list<value_type>::iterator s21::list<value_type>::begin() {
  iterator it(head_);
  return it;
}

template <typename value_type>
typename s21::list<value_type>::iterator s21::list<value_type>::end() {
  iterator it(tail_->next);
  return it;
}

// List Capacity----------------------------------------------------------------

template <typename value_type>
bool s21::list<value_type>::empty() const {
  return size_ == 0;
}

template <typename value_type>
typename s21::list<value_type>::size_type s21::list<value_type>::size() const {
  return size_;
}

template <typename value_type>
typename s21::list<value_type>::size_type s21::list<value_type>::max_size()
    const {
  return std::numeric_limits<size_type>::max() / sizeof(Node_list<value_type>) /
         2;
}

// List Modifiers---------------------------------------------------------------

template <typename value_type>
void s21::list<value_type>::clear() {
  for (size_type i = size_; i > 0; i--) {
    pop_back();
  }
}

template <typename value_type>
typename s21::list<value_type>::iterator s21::list<value_type>::insert(
    iterator pos, const_reference value) {
  if (pos == begin()) {
    push_front(value);
    return begin();
  } else if (pos == end()) {
    push_back(value);
    return end();
  } else {
    Node_list<value_type> *tmp =
        new Node_list<value_type>(pos.curr->prev, pos.curr, value);
    pos.curr->prev->next = tmp;
    pos.curr->prev = tmp;
    size_++;
    return tmp;
  }
}

template <typename value_type>
void s21::list<value_type>::erase(iterator pos) {
  if (pos.curr == nullptr)
    throw std::invalid_argument("Error: invalid iterator");
  if (pos == begin()) {
    pop_front();
  } else if (pos == end()) {
    pop_back();
  } else {
    pos.curr->prev->next = pos.curr->next;
    pos.curr->next->prev = pos.curr->prev;
    Node_list<value_type> *tmp = pos.curr;
    pos.curr = pos.curr->next;
    delete tmp;
    size_--;
  }
}

template <typename value_type>
void s21::list<value_type>::push_back(const_reference value_) {
  if (size_ == 0) {
    head_->value = value_;
  } else {
    tail_->next = new Node_list<value_type>(tail_, nullptr, value_);
    tail_ = tail_->next;
  }
  size_++;
}

template <typename value_type>
void s21::list<value_type>::pop_back() {
  if (size_ == 0) throw std::invalid_argument("Error: invalid size");
  if (size_ == 1) {
    head_->value = 0;
  } else {
    Node_list<value_type> *tmp = tail_->prev;
    if (tail_->prev) tail_->prev->next = nullptr;
    delete tail_;
    tail_ = tmp;
  }
  size_--;
}

template <typename value_type>
void s21::list<value_type>::push_front(const_reference value_) {
  if (size_ == 0) {
    head_->value = value_;
  } else {
    Node_list<value_type> *tmp =
        new Node_list<value_type>(nullptr, head_, value_);
    head_->prev = tmp;
    head_ = tmp;
  }
  size_++;
}

template <typename value_type>
void s21::list<value_type>::pop_front() {
  if (size_ == 0) throw std::runtime_error("The List is empty");
  if (size_ == 1) {
    head_->value = 0;
  } else {
    Node_list<value_type> *tmp = head_;
    head_ = head_->next;
    head_->prev = nullptr;
    delete tmp;
  }
  size_--;
}

template <typename value_type>
void s21::list<value_type>::swap(list &other) {
  std::swap(size_, other.size_);
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
}

//Удаляет элементы из списка аргументов, вставляет их в список назначения
//и сортирует новый объединенный набор элементов по возрастанию или в ином
//указанном порядке
template <typename value_type>
void s21::list<value_type>::merge(list &other) {
  tail_->next = other.head_;
  other.head_->prev = tail_;
  tail_ = other.tail_;
  size_ += other.size_;
  other.head_ = new Node_list<value_type>(nullptr, nullptr, 0);
  other.tail_ = other.head_;
  other.size_ = 0;
  sort();
}

//Удаляет элементы из списка аргументов и вставляет их в список назначения
template <typename value_type>
void s21::list<value_type>::splice(const_iterator pos, list &other) {
  if (pos.curr == nullptr)
    throw std::invalid_argument("Error: invalid iterator");
  if (pos == begin()) {
    other.tail_->next = head_;
    head_->prev = other.tail_;
    head_ = other.head_;
  } else if (pos == end()) {
    tail_->next = other.head_;
    other.head_->prev = tail_;
    tail_ = other.tail_;
  } else {
    iterator it_pos = pos;
    it_pos.curr->prev->next = other.head_;
    other.head_ = it_pos.curr->prev;
    other.tail_->next = it_pos.curr;
    it_pos.curr->prev = other.tail_;
  }
  size_ += other.size_;
  other.tail_ = nullptr;
  other.head_ = nullptr;
  other.size_ = 0;
}

template <typename value_type>
void s21::list<value_type>::reverse() {
  s21::list<value_type> tmp;
  while (!empty()) {
    tmp.push_back(back());
    pop_back();
  }
  swap(tmp);
}

//удаляет последовательные повторяющиеся элементы
template <typename value_type>
void s21::list<value_type>::unique() {
  // if (size_ == 0 || size_ == 1)
  //   return;
  auto it = begin();
  while (it != end()) {
    auto tmp_it = it;
    ++tmp_it;
    if (tmp_it != nullptr && it.curr->value == tmp_it.curr->value) {
      erase(tmp_it);
    } else {
      ++it;
    }
  }
}

template <typename value_type>
void s21::list<value_type>::sort() {
  if (empty()) throw std::invalid_argument("Error: the list is empty!");
  auto pos = begin();
  auto m = 0;
  while (pos != end()) {
    auto pos1 = pos;
    ++pos1;

    auto n = size_ - m - 1;
    while (n) {
      if (pos1.curr->value < pos.curr->value) {
        std::swap(pos.curr->value, pos1.curr->value);
      }
      ++pos1;
      n--;
    }
    ++pos;
    m++;
  }
}

// допы
template <typename value_type>
template <typename... Args>
typename s21::list<value_type>::iterator s21::list<value_type>::emplace(
    const_iterator pos, Args &&... args) {
  const size_type sizeArgs = sizeof...(args);
  value_type arrayArgs[sizeArgs] = {args...};
  for (size_type i = 0; i < sizeArgs; ++i) {
    pos = insert(pos, arrayArgs[i]);
    ++pos;
  }

  return --pos;
}

template <typename value_type>
template <typename... Args>
void s21::list<value_type>::emplace_back(Args &&... args) {
  const size_type sizeArgs = sizeof...(args);
  value_type arrayArgs[sizeArgs] = {args...};
  for (size_type i = 0; i < sizeArgs; ++i) {
    push_back(arrayArgs[i]);
  }
}

template <typename value_type>
template <typename... Args>
void s21::list<value_type>::emplace_front(Args &&... args) {
  const size_type sizeArgs = sizeof...(args);
  value_type arrayArgs[sizeArgs] = {args...};
  for (size_type i = 0; i < sizeArgs; ++i) {
    push_front(arrayArgs[i]);
  }
}

// valgrind --leak-check=full --show-leak-kinds=all -s ./test
// clang-format -i *.cpp *.h *.inl
