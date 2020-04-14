#pragma once

#include <iterator>

#include "TLfwd.hpp"

namespace TL {

    template <typename TList, std::size_t I, std::size_t N = length<TList>::value>
    struct iterator_properties;

    template <typename TList, std::size_t I, bool = iterator_properties<TList, I>::at_start,
                                            bool = iterator_properties<TList, I>::at_end>
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
