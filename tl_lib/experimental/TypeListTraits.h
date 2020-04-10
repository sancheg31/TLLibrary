#pragma once

#include <cstddef>
#include <type_traits>

#include "TypeList.h"
#include "TypeTraits.h"

namespace TL {
namespace experimental {

    /*
     * forward declaration
     * */
    template <typename TList>
    struct size;

    template <typename T, typename U>
    struct size<TypeList<T, U>>
    {
        enum { value = 1 + size<U>::value };
    };

    template <typename T>
    struct size<TypeList<T, NullType>>
    {
        enum { value = 1 };
    };

    template <>
    struct size<TypeList<NullType, NullType>>
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
    struct type_count;

    template <typename TList, typename Type>
    struct type_count_impl;

    template <typename T, typename U, typename Type>
    struct type_count<TypeList<T, U>, Type>: invalid_argument<Type>
    {
        enum { value = type_count_impl<TypeList<T, U>, Type>::value };
    };

    template <typename T, typename U, typename Type>
    struct type_count_impl<TypeList<T, U>, Type>
    {
        enum { value = 0 + type_count<U, Type>::value };
    };

    template <typename U, typename Type>
    struct type_count_impl<TypeList<Type, U>, Type>
    {
        enum { value = 1 + type_count<U, Type>::value };
    };

    template <typename T, typename Type>
    struct type_count_impl<TypeList<T, NullType>, Type>
    {
        enum { value = 0 };
    };

    template <typename Type>
    struct type_count_impl<TypeList<Type, NullType>, Type>
    {
        enum { value = 1 };
    };

    /*
     * forward declaration
     * */
    template <typename TList, typename Type>
    struct has_type;

    template <typename TList, typename Type>
    struct has_type_impl;

    template <typename T, typename U, typename Type>
    struct has_type<TypeList<T, U>, Type>: invalid_argument<Type>
    {
        enum { value = has_type_impl<TypeList<T, U>, Type>::value };
    };

    template <typename T, typename U, typename Type>
    struct has_type_impl<TypeList<T, U>, Type>
    {
        enum { value = has_type<U, Type>::value };
    };

    template <typename U, typename Type>
    struct has_type_impl<TypeList<Type, U>, Type>
    {
        enum { value = true };
    };

    template <typename T, typename Type>
    struct has_type_impl<TypeList<T, NullType>, Type>
    {
        enum { value = false };
    };

    template <typename Type>
    struct has_type_impl<TypeList<Type, NullType>, Type>
    {
        enum { value = true };
    };

    /*
     * forward declaration
     * */
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

    template <typename T>
    struct get_type<TypeList<T, NullType>, 0>
    {
        using type = T;
    };

    template <typename T, std::size_t N>
    struct get_type<TypeList<T, NullType>, N>: experimental::index_out_of_range<N> { };

    template <std::size_t N>
    struct get_type<TypeList<NullType, NullType>, N>: experimental::index_out_of_range<N> { };

} //experimental
} //tl
