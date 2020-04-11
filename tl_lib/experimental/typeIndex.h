#pragma once

#include "TLfwd.hpp"
#include "type_list.hpp"
#include "TLTraits.hpp"

namespace TL {
namespace experimental {

    template <typename TList, typename Type>
    struct type_index;

    template <typename TList, typename Type, std::size_t I = 0>
    struct type_index_impl;

    template <typename TList, typename Type>
    struct last_type_index;

    template <typename TList, typename Type, std::size_t I = 0, int Position = -1>
    struct last_type_index_impl;

    template <typename TList, typename Type>
    struct type_index:    requires::is_type_list<TList>,
                                requires::is_plain_type<Type>,
                                requires::is_not_nulltype<Type>
    {
        enum { value =  type_index_impl<TList, Type>::value };
    };

    template <typename TList, typename Type>
    struct last_type_index: requires::is_type_list<TList>,
                            requires::is_plain_type<Type>,
                            requires::is_not_nulltype<Type>
    {
        enum { value = last_type_index_impl<TList, Type>::value };
    };


    template <typename T, typename ... Tp, typename Type, std::size_t I>
    struct type_index_impl<type_list<T, Tp...>, Type, I>
    {
        enum { value = type_index_impl<type_list<Tp...>, Type, I + 1>::value };
    };

    template <typename ... Tp, typename Type, std::size_t I>
    struct type_index_impl<type_list<Type, Tp...>, Type, I>
    {
        enum { value = I };
    };

    template <typename Type, std::size_t I>
    struct type_index_impl<type_list<>, Type, I>
    {
        enum { value = -1 };
    };


    template <typename T, typename ... Tp, typename Type, int Position, std::size_t I>
    struct last_type_index_impl<type_list<T, Tp...>, Type, I, Position>
    {
        enum { value = last_type_index_impl<type_list<Tp...>, Type, I+1, Position>::value };
    };

    template <typename ... Tp, typename Type, std::size_t I, int Position>
    struct last_type_index_impl<type_list<Type, Tp...>, Type, I, Position>
    {
        enum { value = last_type_index_impl<type_list<Tp...>, Type, I+1, I>::value };
    };

    template <typename Type, std::size_t I, int Position>
    struct last_type_index_impl<type_list<>, Type, I, Position>
    {
        enum { value = Position };
    };






} //experimental
} //tl



