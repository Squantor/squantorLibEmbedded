/*
SPDX-License-Identifier: MIT

Copyright (c) 2020-2020 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/** \file array.hpp

 \brief definition of the array datatype

 Definition of the array datatype
 */
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>

namespace util {
namespace detail {}
/** \brief Standard array type modeled after std::array

Standard array modeled after the C++ std::array type.

\param[in] T typename
\param[in] N size of array
*/
template <typename T, size_t N>
struct array {
  /** \brief Shorthand for defining iterators */
  using iterator = T*;
  /** \brief Shorthand for defining const iterators */
  using const_iterator = const T*;

  /** \brief Return size of the array
  \return Size of the array
  */
  constexpr size_t size() const {
    return N;
  }

  /** \brief Return if the array is empty
  \return true if the array is empty
  */
  constexpr bool empty() const {
    return N == 0;
  }

  /** \brief Return a pointer to the internal array
  \return Pointer of type to C style array
  */
  constexpr T* data() {
    return &__data[0];
  }

  /** \brief Return a const pointer to the internal array
  \return Const pointer of type to C style array
  */
  constexpr const T* data() const {
    return &__data[0];
  }

  /** \brief Indexing operator
  \param n index to the element
  \return reference to the indexed element
  */
  constexpr T& operator[](size_t n) {
    return __data[n];
  }

  /** \brief Const indexing operator
  \param n index to the element
  \return reference to the indexed element used for const arrays
  */
  constexpr const T& operator[](size_t n) const {
    return __data[n];
  }

  /** \brief return first element
  \return reference to the first element in the array
  */
  constexpr T& front() {
    return __data[0];
  }

  /** \brief return first const element
  \return reference to the first const element in the array
  */
  constexpr const T& front() const {
    return __data[0];
  }

  /** \brief return last element
  \return reference to the last element in the array
  */
  constexpr T& back() {
    return __data[N - 1];
  }

  /** \brief return last const element
  \return reference to the last const element in the array
  */
  constexpr const T& back() const {
    return __data[N - 1];
  }

  /** \brief return begin pointer of array
  \return pointer to the first element in the array
  */
  constexpr iterator begin() {
    return &__data[0];
  }

  /** \brief return begin pointer of const array
  \return pointer to the first const element in the array
  */
  constexpr const_iterator begin() const {
    return &__data[0];
  }

  /** \brief return begin pointer of const array
  \return pointer to the first const element in the array
  */
  constexpr const_iterator cbegin() const {
    return &__data[0];
  }

  /** \brief return end pointer of array
  \return pointer beyond the last element in the array
  */
  constexpr iterator end() {
    return &__data[N];
  }

  /** \brief return end pointer of const array
  \return pointer beyond the last const element in the array
  */
  constexpr const_iterator end() const {
    return &__data[N];
  }

  /** \brief return end pointer of const array
  \return pointer beyond the last const element in the array
  */
  constexpr const_iterator cend() const {
    return &__data[N];
  }

  /** \brief Array structure containing data */
  T __data[N];
};
}  // namespace util

#endif