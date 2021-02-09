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
        
        using iterator = T*;

        void reset()
        {
            for(auto i = buffer.begin(); i != buffer.end(); i++)
                *i = 0;
            sum = 0;
            front = buffer.begin();
        }

        void add(T value)
        {
            T temp = *front;
            sum -= temp;
            *front = value;
            sum += value;
            front++;
            if(front == buffer.end())
                front = buffer.begin(); 
        }

        T get()
        {
            return sum / N;
        }

        iterator front;
        T sum;
        util::array<T, N> buffer;
    };
}


#endif