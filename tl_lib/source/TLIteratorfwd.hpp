#pragma once

#include <iterator>

#include "TLfwd.hpp"

namespace TL {

    template <typename TIter>
    struct iterator_properties;

    template <typename TList, std::size_t I, bool = (I == 0), bool = (I == length<TList>::value)>
    struct type_list_iterator;

    template <typename TList>
    struct begin;

    template <typename TList>
    struct end;

    template <typename Iter, int Distance>
    struct advance;

    template <typename Iter>
    struct next;

    template <typename Iter>
    struct prev;

    template <typename Iter1, typename Iter2>
    struct distance;

    template <typename TList, std::size_t I1, std::size_t I2>
    inline constexpr bool operator==(type_list_iterator<TList, I1>&&, type_list_iterator<TList, I2>&&);

    template <typename TList, std::size_t I1, std::size_t I2>
    inline constexpr bool operator!=(type_list_iterator<TList, I1>&&, type_list_iterator<TList, I2>&&);

    template <typename TList, std::size_t I1, std::size_t I2>
    inline constexpr bool operator<(type_list_iterator<TList, I1>&&, type_list_iterator<TList, I2>&&);

}
