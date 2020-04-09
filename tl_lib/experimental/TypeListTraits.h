#pragma once

#include <cstddef>
#include "TypeList.h"

namespace TL {
namespace experimental {

    /*
     * forward declaration
     * */
    template <typename TList>
    struct length;

    template <typename T, typename U>
    struct length<TypeList<T, U>>
    {
        enum { value = 1 + length<U>::value };
    };

    template <typename T>
    struct length<TypeList<T, NullType>>
    {
        enum { value = 1 };
    };

    template <>
    struct length<TypeList<NullType, NullType>>
    {
        enum { value = 0 };
    };


    /*
     * forward declaration
     * */
    template <typename TList>
    struct empty;

    template <typename T, typename U>
    struct empty<TypeList<T, U>>
    {
        enum { value = false };
    };

    template <>
    struct empty<TypeList<NullType, NullType>>
    {
        enum { value = true };
    };

    /*
     * forward declaration
     * */
    template <typename TList, typename Type>
    struct has_type;

    template <typename TList>
    struct has_type<TList, NullType>;

    template <typename T, typename U, typename Type>
    struct has_type<TypeList<T, U>, Type>
    {
        enum { value = has_type<U, Type>::value };
    };

    template <typename U, typename Type>
    struct has_type<TypeList<Type, U>, Type>
    {
        enum { value = true };
    };

    template <typename T, typename Type>
    struct has_type<TypeList<T, NullType>, Type>
    {
        enum { value = false };
    };

    template <typename Type>
    struct has_type<TypeList<NullType, NullType>, Type>
    {
        enum { value = false };
    };


    template <typename TList, std::size_t N>
    struct get_type;

    template <typename T, typename U, std::size_t N>
    struct get_type<TypeList<T, U>, N>
    {
        using type = typename get_type<U, N-1>::type;
    };

    template <typename T, typename U>
    struct get_type<TypeList<T, U>, 0>
    {
        using type = T;
    };

    template <typename T, std::size_t N>
    struct get_type<TypeList<T, NullType>, N> { };

    template <std::size_t N>
    struct get_type<TypeList<NullType, NullType>, N> { };

} //experimental
} //tl
