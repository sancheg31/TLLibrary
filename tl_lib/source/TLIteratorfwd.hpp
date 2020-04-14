#pragma once

#include <iterator>

#include "TLfwd.hpp"

namespace TL {

    template <typename TList, std::size_t I, std::size_t N = length<TList>::value>
    struct iterator_properties;

    template <typename TList, std::size_t I, bool = iterator_properties<TList, I>::at_start,
                                            bool = iterator_properties<TList, I>::at_end>
    struct type_list_iterator;

    template <typename ... Tp>
    type_list_iterator<type_list<Tp...>, 0> begin(type_list<Tp...>&&);

    template <typename TList>
    type_list_iterator<TList, 0> begin();

    template <typename ... Tp>
    type_list_iterator<type_list<Tp...>, length<type_list<Tp...>>::value> end(type_list<Tp...>&&);

    template <typename TList>
    type_list_iterator<TList, length<TList>::value> end();

    template <typename TList, std::size_t I, int Distance>
    constexpr TL::type_list_iterator<TList, I + Distance>
    advance(TL::type_list_iterator<TList, I> &&);

    template <typename TList, std::size_t I>
    constexpr TL::type_list_iterator<TList, I + 1>
    next(TL::type_list_iterator<TList, I>&&);

    template <typename TList, std::size_t I>
    constexpr TL::type_list_iterator<TList, I-1>
    prev(TL::type_list_iterator<TList, I>&&);

    template <typename TList, std::size_t I1, std::size_t I2>
    constexpr typename std::iterator_traits<TL::type_list_iterator<TList, I1>>::difference_type
    distance(TL::type_list_iterator<TList, I1>&&, TL::type_list_iterator<TList, I2>&&);

    template <typename TList, std::size_t I1, std::size_t I2>
    inline constexpr bool operator==(type_list_iterator<TList, I1>&&, type_list_iterator<TList, I2>&&);

    template <typename TList, std::size_t I1, std::size_t I2>
    inline constexpr bool operator!=(type_list_iterator<TList, I1>&&, type_list_iterator<TList, I2>&&);

    template <typename TList, std::size_t I1, std::size_t I2>
    inline constexpr bool operator<(type_list_iterator<TList, I1>&&, type_list_iterator<TList, I2>&&);

}
