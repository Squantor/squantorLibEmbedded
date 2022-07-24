/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file moving_average.hpp
 *
 * Implements a moving average filter
 *
 */
#ifndef MOVING_AVERAGE_HPP
#define MOVING_AVERAGE_HPP

#include <array.hpp>

namespace util {
template <typename T, size_t N>
class MovingAverage {
 public:
  using iterator = typename util::array<T, N>::iterator;

  MovingAverage(T value) {
    reset(value);
  }

  void reset(T value) {
    sum = 0;
    for (auto& v : __data) {
      v = value;
      sum += value;
    }
    front = __data.begin();
  }

  void add(T value) {
    auto temp = *front;
    sum -= temp;
    *front = value;
    sum += value;
    front += 1;
    if (front == __data.end()) front = __data.begin();
  }

  const T get() {
    return sum / static_cast<T>(__data.size());
  }

 private:
  iterator front;
  T sum;
  util::array<T, N> __data;
};
}  // namespace util

#endif