/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** 
 *\file ringbuffer.hpp
 * 
 * Implements a ringbuffer
 * 
 */ 
#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <array.hpp>

namespace util
{
    template<typename T, size_t N>
    class RingBuffer {
    public:
        using iterator = typename util::array<T, N>::iterator;
        RingBuffer()
        {
            reset();
        }

        void reset()
        {
            front = __data.begin();
            back = __data.begin();
        }

        bool full()
        {
            auto temp = front + 1;
            if(temp == __data.end())
                temp = __data.begin();
            if(temp == back)
                return true;
            else
                return false;
        }

        bool empty()
        {
            if(front == back)
                return true;
            else
                return false;
        }

    private:
        iterator front;
        iterator back;
        util::array<T, N> __data;
    };
}

#endif