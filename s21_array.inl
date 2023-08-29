#include "s21_array.h"

// Array Member functions ------------------------------------------------

template <typename value_type, std::size_t N>
s21::array<value_type, N>::array(
    std::initializer_list<value_type> const &items) {
  size_type i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr_[i] = *it;
    i++;
  }

  if (items.size() < N) {  // TODO: проверить, точно ли надо эту часть
    for (; i < N; i++) {
      arr_[i] = 0;
    }
  }
}

template <typename value_type, std::size_t N>
s21::array<value_type, N>::array(const array &other) : array() {
  if (this != &other) {
    for (size_type i = 0; i < N; i++) arr_[i] = other.arr_[i];
  }
}

template <typename value_type, std::size_t N>
s21::array<value_type, N>::array(array &&other) {
  *this = std::move(other);
}

template <typename value_type, std::size_t N>
s21::array<value_type, N> &s21::array<value_type, N>::operator=(
    array &&other) {  // TODO: проверить
  if (this != &other) {
    for (size_type i = 0; i < N; i++) arr_[i] = other.arr_[i];
  }
  return *this;
}

template <typename value_type, std::size_t N>
s21::array<value_type, N> &s21::array<value_type, N>::operator=(
    const array &other) {  // TODO: проверить
  if (this != &other) {
    if (size_ != other.size_) {
      throw std::length_error("Error");
    }
    for (size_type i = 0; i < N; i++) {
      arr_[i] = other[i];
    }
  }

  return *this;
}

// Array Element access --------------------------------------------------

template <typename value_type, std::size_t N>
typename s21::array<value_type, N>::reference s21::array<value_type, N>::at(
    size_type position) {
  if (position >= size_) throw std::invalid_argument("Invalid index");
  return arr_[position];
}

template <typename value_type, std::size_t N>
typename s21::array<value_type, N>::const_reference
s21::array<value_type, N>::front() {
  if (size_ == 0) throw std::out_of_range("The array contains no elements");
  return *arr_;
}

template <typename value_type, std::size_t N>
typename s21::array<value_type, N>::const_reference
s21::array<value_type, N>::back() {
  if (size_ == 0) throw std::out_of_range("The array contains no elements");
  return *(arr_ + size_ - 1);
}

// Array Modifiers -------------------------------------------------------

template <typename value_type, std::size_t N>
void s21::array<value_type, N>::swap(array &other) {
  if (this != &other || size_ != other.size_) {
    std::swap(size_, other.size_);
    std::swap(arr_, other.arr_);
  }
}

template <typename value_type, std::size_t N>
void s21::array<value_type, N>::fill(const_reference value) {
  if (size_ != 0) {
    for (size_t i = 0; i < size_; ++i) arr_[i] = value;
  }
}