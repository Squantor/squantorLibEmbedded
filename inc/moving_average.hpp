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

namespace util
{
    template<typename T, size_t N>
    struct movingAverage {

        util::array<T, N> buffer;
    };
}


#endif