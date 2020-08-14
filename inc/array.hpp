/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2020-2020 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** 
 * \file array.hpp
 * 
 * definition of the array datatype
 * 
 * Definition of the array datatype
 */ 
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>

namespace util
{
    namespace detail
    {
    }
    /**
     * \brief Standard array type modeled after std::array
     * 
     * Standard array modeled after the C++ std::array type.
     * 
     * \param[in] T typename
     * \param[in] N size of array
     */
    template<typename T, size_t N>
    struct array 
    {
        size_t size() { return N; }

        bool empty() { return N == 0; }

        T *data() {return &__data[0]; }

        T __data[N]; /** Data store used internally */
    };
}

#endif