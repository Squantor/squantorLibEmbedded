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

        bool PushBack(T& p)
        {
            iterator temp;
            if(back == __data.begin())
                temp = __data.end() - 1;
            else
                temp = back - 1;
            if(front == temp)
                return false;
            back = temp;
            *back = p;
            return true;
        }

        bool PushFront(T& p)
        {
            auto temp = front + 1;
            if(temp == __data.end() + 1)
                temp = __data.begin();
            if(back == temp)
                return false;
            *front = p;
            front = temp;
            return true;
        }

        bool PopBack(T& p)
        {
            if(back == front)
                return false;
            auto temp = back + 1;
            if(temp == __data.end() + 1)
                temp = 0;
            p = *back;
            back = temp;
            return true;
        }
        
        bool PopFront(T& p)
        {
            if(back == front)
                return false;
            iterator temp;
            if(front == __data.begin())
                temp = __data.end() - 1;
            else
                temp = front - 1;
            p = *temp;
            front = temp;
            return true;
        }

    private:
        iterator front;
        iterator back;
        util::array<T, N+1> __data;
    };
}

#endif