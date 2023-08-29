#include "s21_vector.h"

// vector Member functions---------------------------------------------------

template <typename value_type>
s21::vector<value_type>::vector() : size_(0u), capacity_(0u), arr_(nullptr) {}

template <typename value_type>
s21::vector<value_type>::vector(size_type size) : size_(size), capacity_(size) {
  if (size)
    arr_ = new value_type[size_]();
  else
    arr_ = nullptr;
}

template <typename value_type>
s21::vector<value_type>::vector(
    std::initializer_list<value_type> const &items) {
  arr_ = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr_[i] = *it;
    i++;
  }
  size_ = items.size();
  capacity_ = items.size();
}

template <typename value_type>
s21::vector<value_type>::vector(const vector &other) : vector() {
  *this = other;
}

template <typename value_type>
s21::vector<value_type>::vector(vector &&other)
    : size_(other.size_), capacity_(other.capacity_), arr_(other.arr_) {
  other.arr_ = nullptr;
  other.size_ = 0;
}

template <typename value_type>
s21::vector<value_type>::~vector() {
  delete[] arr_;
}

//перегрузка оператора = ---------------------------------------------------

template <typename value_type>
s21::vector<value_type> &s21::vector<value_type>::operator=(
    const vector &other) {
  if (this != &other) {
    if (other.size_ > capacity_) {
      capacity_ = other.capacity_;
      delete[] arr_;
      arr_ = new value_type[capacity_];
    }
    for (size_type i = 0; i < other.size_; i++) {
      arr_[i] = other.arr_[i];
    }
    size_ = other.size_;
  }
  return *this;
}

template <typename value_type>
s21::vector<value_type> &s21::vector<value_type>::operator=(vector &&other) {
  if (this != &other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    delete[] arr_;
    arr_ = other.arr_;
    other.arr_ = nullptr;
  }
  return *this;
}

// vector Element access----------------------------------------------------

template <typename value_type>
typename s21::vector<value_type>::reference s21::vector<value_type>::at(
    size_type position) {
  if (position >= size_) throw std::out_of_range("Error");
  return arr_[position];
}

template <typename value_type>
typename s21::vector<value_type>::reference s21::vector<value_type>::operator[](
    size_type position) {
  return arr_[position];
}

template <typename value_type>
typename s21::vector<value_type>::const_reference
s21::vector<value_type>::operator[](size_type position) const {
  return arr_[position];
}

template <typename value_type>
typename s21::vector<value_type>::const_reference
s21::vector<value_type>::front() {
  if (!arr_) throw std::out_of_range("The vector contains no elements");
  return arr_[0];
}

template <typename value_type>
typename s21::vector<value_type>::const_reference
s21::vector<value_type>::back() {
  if (!arr_) throw std::out_of_range("The vector contains no elements");
  return arr_[size_ - 1];
}

template <typename value_type>
typename s21::vector<value_type>::iterator s21::vector<value_type>::data() {
  return arr_;
}

// vector Iterators---------------------------------------------------------

template <typename value_type>
typename s21::vector<value_type>::iterator s21::vector<value_type>::begin() {
  return arr_;
}

template <typename value_type>
typename s21::vector<value_type>::iterator s21::vector<value_type>::end() {
  return arr_ + size_;
}

// vector Capacity----------------------------------------------------------

template <typename value_type>
bool s21::vector<value_type>::empty() {
  return size_ == 0;
}

template <typename value_type>
typename s21::vector<value_type>::size_type s21::vector<value_type>::size() {
  return size_;
}

template <typename value_type>
typename s21::vector<value_type>::size_type
s21::vector<value_type>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
}

template <typename value_type>
void s21::vector<value_type>::reserve(size_type new_capacity) {
  if (new_capacity <= capacity_) return;

  iterator newarr =
      reinterpret_cast<iterator>(new int8_t[new_capacity * sizeof(value_type)]);

  try {
    std::uninitialized_copy(arr_, arr_ + size_, newarr);
  } catch (...) {
    delete[] reinterpret_cast<int8_t *>(newarr);
    throw;
  }

  for (size_t i = 0; i < size_; i++) {
    (arr_ + i)->~value_type();
  }

  delete[] reinterpret_cast<int8_t *>(arr_);

  arr_ = newarr;
  capacity_ = new_capacity;
}

template <typename value_type>
typename s21::vector<value_type>::size_type
s21::vector<value_type>::capacity() {
  return capacity_;
}

template <typename value_type>
void s21::vector<value_type>::shrink_to_fit() {
  if (size_ == capacity_) return;
  reserve(size_);
  capacity_ = size_;
}

// vector Modifiers---------------------------------------------------------

template <typename value_type>
void s21::vector<value_type>::clear() {
  size_ = 0;
}

template <typename value_type>
typename s21::vector<value_type>::iterator s21::vector<value_type>::insert(
    iterator position, const_reference value) {
  size_type index = position - arr_;
  if (index >= size_) throw std::invalid_argument("Error: invalid pointer");
  if (size_ == capacity_) {
    reserve(capacity_ * 2);
  }
  for (size_type i = size_, j = size_ - 1; i > 0; i--, j--) {
    arr_[i] = arr_[j];
    if (i == index) {
      arr_[i] = value;
      j++;
    }
  }
  size_++;
  arr_[index] = value;
  position = arr_ + index;
  return position;
}

template <typename value_type>
void s21::vector<value_type>::erase(iterator position) {
  size_type index = position - arr_;
  if (size_ == 0 || index >= size_)
    throw std::invalid_argument("Error: invalid pointer");
  for (size_type i = index; i < size_ - 1; i++) {
    arr_[i] = arr_[i + 1];
  }
  size_--;
}

template <typename value_type>
void s21::vector<value_type>::push_back(const_reference value) {
  if (size_ == capacity_) {
    if (capacity_ == 0) {
      reserve(capacity_ + 1);
    } else {
      reserve(capacity_ * 2);
    }
  }
  new (arr_ + size_) value_type(value);
  size_++;
}

template <typename value_type>
void s21::vector<value_type>::pop_back() {
  if (size_) {
    (arr_ + size_ - 1)->~value_type();
    size_--;
  }
}

template <typename value_type>
void s21::vector<value_type>::swap(s21::vector<value_type> &other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(arr_, other.arr_);
}

// допы
template <typename value_type>
template <typename... Args>
typename s21::vector<value_type>::iterator s21::vector<value_type>::emplace(
    const_iterator pos, Args &&... args) {
  const size_type sizeArgs = sizeof...(args);

  s21::vector<value_type> temp{args...};
  value_type *res = const_cast<value_type *>(pos);

  for (size_type i = 0; i < sizeArgs; ++i) {
    res = insert(res, temp[i]);
    ++res;
  }

  return --res;
}

template <typename value_type>
template <typename... Args>
void s21::vector<value_type>::emplace_back(Args &&... args) {
  const size_type sizeArgs = sizeof...(args);

  s21::vector<value_type> temp{args...};
  for (size_type i = 0; i < sizeArgs; ++i) {
    push_back(temp[i]);
  }
}

// valgrind --leak-check=full --show-leak-kinds=all -s ./test
// clang-format -i *.cpp *.h *.inl
