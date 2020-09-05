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

namespace util
{
    namespace detail
    {
    }
    /** \brief Standard array type modeled after std::array
     
    Standard array modeled after the C++ std::array type.
    
    \param[in] T typename
    \param[in] N size of array
    */
    template<typename T, size_t N>
    struct array 
    {
        /** \brief Return size of the array 
        \return Size of the array
        */
        constexpr size_t size() const { return N; }

        /** \brief Return if the array is empty 
        \return true if the array is empty
        */
        constexpr bool empty() const { return N == 0; }

        /** \brief Return a pointer to actual array 
        \return Pointer of type to C style array
        */
        constexpr T *data() { return &__data[0]; }

        /** \brief Indexing operator
        \return reference to the indexed element
        */
        constexpr T& operator[](size_t n) { return __data[n]; }

        /** \brief Const indexing operator
        \return reference to the indexed element used for const arrays
        */
        constexpr const T& operator[](size_t n) const { return __data[n]; }

        


        T __data[N]; /** Data store used internally */
    };
}

#endif