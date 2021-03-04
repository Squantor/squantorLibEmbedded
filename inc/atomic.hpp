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

namespace util
{
    /** \brief memory order variants */
    enum class memory_order { relaxed, consume, acquire, release, acq_rel, seq_cst };

    namespace detail
    {
        /** \brief Translate memory_order into GCC memory ordering
        \param mo memory order to translate into GCC memory ordering
        \return GCC style memory ordering value
        */
        constexpr int to_atomic_memorder(const memory_order mo)
        {
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

        constexpr memory_order get_default_memory_order()
        {
            // Safest, but also slowest
            return memory_order::seq_cst;
        }

    }

    /** \brief Standard atomic type modeled after std::atomic
     
    Standard atomic type modeled after the C++ std::atomic type.
    
    \param[in] T typename
    */
    template<typename T>
    class atomic
    {
      public:
        /** \brief **/
        atomic(T value = {}) noexcept 
        { 
            store(value); 
        }

        /** \brief **/
        atomic(const atomic& a) = delete;

        /** \brief **/
        atomic& operator=(const atomic& a) = delete;
        
        /** \brief 
        \param value 
        \param mo
        \return
        **/
        void store(T value, memory_order mo = detail::get_default_memory_order()) noexcept
        {
            __atomic_store(&a_value, &value, detail::to_atomic_memorder(mo));
        }

        /** \brief 
        \param value 
        \return
        **/
        T operator=(T value) noexcept
        {
            store(value);
            return value;
        }

        /** \brief 
        \param 
        \return
        **/
        T load(memory_order mo = detail::get_default_memory_order()) const noexcept
        {
            T value;
            __atomic_load(&a_value, &value, detail::to_atomic_memorder(mo));
            return value;
        }

        /** \brief 
        \param 
        \return
        **/
        operator T() const noexcept 
        { 
            return load(); 
        }

        /** \brief 
        \param 
        \return
        **/
        T fetch_add(T arg, memory_order mo = detail::get_default_memory_order()) noexcept
        {
            return __atomic_fetch_add(&a_value, arg, detail::to_atomic_memorder(mo));
        }

        /** \brief 
        \param 
        \return
        **/
        T fetch_sub(T arg, memory_order mo = detail::get_default_memory_order()) noexcept
        {
            return __atomic_fetch_sub(&a_value, arg, detail::to_atomic_memorder(mo));
        }

        /** \brief 
        \param 
        \return
        **/
        T fetch_and(T arg, memory_order mo = detail::get_default_memory_order()) noexcept
        {
            return __atomic_fetch_and(&a_value, arg, detail::to_atomic_memorder(mo));
        }

        /** \brief 
        \param 
        \return
        **/
        T fetch_or(T arg, memory_order mo = detail::get_default_memory_order()) noexcept
        {
            return __atomic_fetch_or(&a_value, arg, detail::to_atomic_memorder(mo));
        }

        /** \brief 
        \param 
        \return
        **/
        T fetch_xor(T arg, memory_order mo = detail::get_default_memory_order()) noexcept
        {
            return __atomic_fetch_xor(&a_value, arg, detail::to_atomic_memorder(mo));
        }

        /** \brief 
        \param 
        \return
        **/
        T exchange(T value, memory_order mo = detail::get_default_memory_order()) noexcept
        {
            T prev;
            __atomic_exchange(&a_value, &value, &prev, detail::to_atomic_memorder(mo));
            return prev;
        }

        /** \brief 
        \param 
        \return
        **/
        bool compare_exchange_weak(
            T& expected, T desired, memory_order success, memory_order failure) noexcept
        {
            return __atomic_compare_exchange(
                &a_value, &expected, &desired, true, detail::to_atomic_memorder(success),
                detail::to_atomic_memorder(failure));
        }

        /** \brief 
        \param 
        \return
        **/
        bool compare_exchange_weak(
            T& expected, T desired,
            memory_order order = detail::get_default_memory_order()) noexcept
        {
            return compare_exchange_weak(expected, desired, order, order);
        }

        /** \brief 
        \param 
        \return
        **/
        bool compare_exchange_strong(
            T& expected, T desired, memory_order success, memory_order failure) noexcept
        {
            return __atomic_compare_exchange(
                &a_value, &expected, &desired, false, detail::to_atomic_memorder(success),
                detail::to_atomic_memorder(failure));
        }

        /** \brief 
        \param 
        \return
        **/
        bool compare_exchange_strong(
            T& expected, T desired,
            memory_order order = detail::get_default_memory_order()) noexcept
        {
            return compare_exchange_strong(expected, desired, order, order);
        }

        /** \brief 
        \param 
        \return
        **/
        T operator++() noexcept 
        { 
            return fetch_add(T{1}) + T{1}; 
        }

        /** \brief 
        \param 
        \return
        **/
        T operator++(int) noexcept 
        { 
            return fetch_add(T{1}); 
        }

        /** \brief 
        \param 
        \return
        **/
        T operator--() noexcept 
        { 
            return fetch_sub(T{1}) - T{1}; 
        }

        /** \brief 
        \param 
        \return
        **/
        T operator--(int) noexcept 
        { 
            return fetch_sub(T{1}); 
        }

        /** \brief 
        \param 
        \return
        **/
        T operator+=(T arg) noexcept 
        { 
            return fetch_add(arg) + arg; 
        }

        /** \brief 
        \param 
        \return
        **/
        T operator-=(T arg) noexcept 
        { 
            return fetch_sub(arg) - arg; 
        }

        /** \brief 
        \param 
        \return
        **/        
        T operator&=(T arg) noexcept 
        { 
            return fetch_and(arg) & arg; 
        }

        /** \brief 
        \param 
        \return
        **/
        T operator|=(T arg) noexcept 
        { 
            return fetch_or(arg) | arg; 
        }

        /** \brief 
        \param 
        \return
        **/
        T operator^=(T arg) noexcept 
        { 
            return fetch_xor(arg) ^ arg; 
        }

      private:
        T a_value;
    };
}

#endif 
