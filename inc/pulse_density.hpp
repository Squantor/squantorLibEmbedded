/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file pulse_density.hpp
 *
 */
#ifndef PULSE_DENSITY_HPP
#define PULSE_DENSITY_HPP

#include <stdint.h>

namespace util {
class PulseDensityModulator {
 public:
  PulseDensityModulator(uint32_t threshold, uint32_t step) : sum(0), threshold(threshold), step(step) {}

  bool output() {
    sum += step;
    if (sum > threshold) {
      sum -= threshold;
      return true;
    } else {
      return false;
    }
  }
  uint32_t sum;
  uint32_t threshold;
  uint32_t step;
};
}  // namespace util

#endif