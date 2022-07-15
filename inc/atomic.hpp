/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/** \file atomic.hpp

\brief definition of the atomic datatype

Definition of the atomic datatype, inspired by zhmu's atomic template
from the Ananas operating system:
https://github.com/zhmu/ananas/blob/master/include/ananas/util/atomic.h
*/
#ifndef ATOMIC_HPP
#define ATOMIC_HPP

#include <cstddef>

namespace util {
/** \brief memory order variants */
enum class memory_order { relaxed, consume, acquire, release, acq_rel, seq_cst };

namespace detail {
/** \brief Translate memory_order into GCC memory ordering
\param mo memory order to translate into GCC memory ordering
\return GCC style memory ordering value
*/
constexpr int to_atomic_memorder(const memory_order mo) {
  switch (mo) {
    case memory_order::relaxed:
      return __ATOMIC_RELAXED;
    case memory_order::consume:
      return __ATOMIC_CONSUME;
    case memory_order::acquire:
      return __ATOMIC_ACQUIRE;
    case memory_order::release:
      return __ATOMIC_RELEASE;
    case memory_order::acq_rel:
      return __ATOMIC_ACQ_REL;
    case memory_order::seq_cst:
      return __ATOMIC_SEQ_CST;
    default:
      return -1;
  }
}

constexpr memory_order get_default_memory_order() {
  // Safest, but also slowest
  return memory_order::seq_cst;
}

}  // namespace detail

/** \brief Standard atomic type modeled after std::atomic

Standard atomic type modeled after the C++ std::atomic type.

\param[in] T typename
*/
template <typename T>
class atomic {
 public:
  /** \brief default constructor **/
  atomic(T value = {}) noexcept {
    store(value);
  }

  /** \brief deleted **/
  atomic(const atomic& a) = delete;

  /** \brief deleted **/
  atomic& operator=(const atomic& a) = delete;

  /** \brief Store value in the atomic object
  \param value object to be stored
  \param mo requested memory order
  **/
  void store(T value, memory_order mo = detail::get_default_memory_order()) noexcept {
    __atomic_store(&a_value, &value, detail::to_atomic_memorder(mo));
  }

  /** \brief Assignment operator
  \param value assignment object
  \return value of the atomic object
  **/
  T operator=(T value) noexcept {
    store(value);
    return value;
  }

  /** \brief returns value of the atomic object
  \param mo memory order
  \return value of the atomic object
  **/
  T load(memory_order mo = detail::get_default_memory_order()) const noexcept {
    T value;
    __atomic_load(&a_value, &value, detail::to_atomic_memorder(mo));
    return value;
  }

  /** \brief
  \param
  \return
  **/
  operator T() const noexcept {
    return load();
  }

  /** \brief adds argument to the atomic object and returns the result
  \param arg object to add
  \param mo memory order to execute this operation with
  \return result of the addition
  **/
  T fetch_add(T arg, memory_order mo = detail::get_default_memory_order()) noexcept {
    return __atomic_fetch_add(&a_value, arg, detail::to_atomic_memorder(mo));
  }

  /** \brief subtracts argument from the atomic object and returns the result
  \param arg object to subtract
  \param mo memory order to execute this operation with
  \return result of the subtraction
  **/
  T fetch_sub(T arg, memory_order mo = detail::get_default_memory_order()) noexcept {
    return __atomic_fetch_sub(&a_value, arg, detail::to_atomic_memorder(mo));
  }

  /** \brief performs a bitwise AND with the atomic object and returns the result
  \param arg object to bitwise AND
  \param mo memory order to execute this operation with
  \return result of the bitwise AND
  **/
  T fetch_and(T arg, memory_order mo = detail::get_default_memory_order()) noexcept {
    return __atomic_fetch_and(&a_value, arg, detail::to_atomic_memorder(mo));
  }

  /** \brief performs a bitwise OR with the atomic object and returns the result
  \param arg object to bitwise OR
  \param mo memory order to execute this operation with
  \return result of the bitwise OR
  **/
  T fetch_or(T arg, memory_order mo = detail::get_default_memory_order()) noexcept {
    return __atomic_fetch_or(&a_value, arg, detail::to_atomic_memorder(mo));
  }

  /** \brief performs a bitwise XOR with the atomic object and returns the result
  \param arg object to bitwise XOR
  \param mo memory order to execute this operation with
  \return result of the bitwise XOR
  **/
  T fetch_xor(T arg, memory_order mo = detail::get_default_memory_order()) noexcept {
    return __atomic_fetch_xor(&a_value, arg, detail::to_atomic_memorder(mo));
  }

  /** \brief replace the value of the atomic object and returns the previous object
  \param value object to exchange
  \param mo memory order to execute this operation with
  \return previously held object
  **/
  T exchange(T value, memory_order mo = detail::get_default_memory_order()) noexcept {
    T prev;
    __atomic_exchange(&a_value, &value, &prev, detail::to_atomic_memorder(mo));
    return prev;
  }

  /** \brief try and compare and exchange the value
  \param expected expected value of the comparison
  \param desired value to load if expected value is found
  \param success ordering for the load operation if the comparison succeeds
  \param failure ordering for the load operation if the operation fails
  \return true if the atomic value has been succesfully changed
  **/
  bool compare_exchange_weak(T& expected, T desired, memory_order success, memory_order failure) noexcept {
    return __atomic_compare_exchange(&a_value, &expected, &desired, true, detail::to_atomic_memorder(success),
                                     detail::to_atomic_memorder(failure));
  }

  /** \brief try and compare and exchange the value
  \param expected expected value of the comparison
  \param desired value to load if expected value is found
  \param order ordering for both operations
  \return true if the atomic value has been succesfully changed
  **/
  bool compare_exchange_weak(T& expected, T desired, memory_order order = detail::get_default_memory_order()) noexcept {
    return compare_exchange_weak(expected, desired, order, order);
  }

  /** \brief try and compare and exchange the value
  \param expected expected value of the comparison
  \param desired value to load if expected value is found
  \param success ordering for the load operation if the comparison succeeds
  \param failure ordering for the load operation if the operation fails
  \return true if the atomic value has been succesfully changed

  The strong version has a higher chance of succeeding then the weak version and is used
  when you do not want a loop like in the weak version.
  **/
  bool compare_exchange_strong(T& expected, T desired, memory_order success, memory_order failure) noexcept {
    return __atomic_compare_exchange(&a_value, &expected, &desired, false, detail::to_atomic_memorder(success),
                                     detail::to_atomic_memorder(failure));
  }

  /** \brief try and compare and exchange the value
  \param expected expected value of the comparison
  \param desired value to load if expected value is found
  \param order ordering for both operations
  \return true if the atomic value has been succesfully changed

  The strong version has a higher chance of succeeding then the weak version and is used
  when you do not want a loop like in the weak version.
  **/
  bool compare_exchange_strong(T& expected, T desired, memory_order order = detail::get_default_memory_order()) noexcept {
    return compare_exchange_strong(expected, desired, order, order);
  }

  /** \brief Prefix increment operator overload
  \return the incremented value
  **/
  T operator++() noexcept {
    return fetch_add(T{1}) + T{1};
  }

  /** \brief Prefix increment operator overload
  \return the incremented value
  **/
  T operator++(int) noexcept {
    return fetch_add(T{1});
  }

  /** \brief Prefix decrement operator overload
  \return the decremented value
  **/
  T operator--() noexcept {
    return fetch_sub(T{1}) - T{1};
  }

  /** \brief Prefix decrement operator overload
  \return the decremented value
  **/
  T operator--(int) noexcept {
    return fetch_sub(T{1});
  }

  /** \brief Addition operator overload
  \param arg value to add to the atomic value
  \return sum of arg and the atomic value
  **/
  T operator+=(T arg) noexcept {
    return fetch_add(arg) + arg;
  }

  /** \brief Subtraction operator overload
  \param arg value to subtract from the atomic value
  \return difference of arg and the atomic value
  **/
  T operator-=(T arg) noexcept {
    return fetch_sub(arg) - arg;
  }

  /** \brief bitwise AND operator overload
  \param arg value to bitwise AND with the atomic value
  \return bitwise AND of arg and the atomic value
  **/
  T operator&=(T arg) noexcept {
    return fetch_and(arg) & arg;
  }

  /** \brief bitwise OR operator overload
  \param arg value to bitwise OR with the atomic value
  \return bitwise OR of arg and the atomic value
  **/
  T operator|=(T arg) noexcept {
    return fetch_or(arg) | arg;
  }

  /** \brief bitwise XOR operator overload
  \param arg value to bitwise XOR with the atomic value
  \return bitwise XOR of arg and the atomic value
  **/
  T operator^=(T arg) noexcept {
    return fetch_xor(arg) ^ arg;
  }

 private:
  /** \brief atomic object */
  T a_value;
};
}  // namespace util

#endif
