#pragma once

#include <cstddef>

#include "tl_node.h"
#include "tl_nulltype.h"
#include "tl_utilities.h"
#include "experimental/TypeTraits.h"

namespace TL {

namespace utilities {

    template <typename T>
    inline constexpr int is_NullType = std::is_same_v<T, NullType>;

    template <typename T, typename U>
    inline constexpr int is_same_safe = utilities::is_same_type<T, U> && !utilities::is_NullType<T>;

} //utilities

namespace Implementation {
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
    struct type_count<TypeList<T, U>, Type>: utilities::invalid_argument<Type>
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
    struct get_type<TypeList<T, NullType>, N>: utilities::index_out_of_range<N> { };

    template <std::size_t N>
    struct get_type<TypeList<NullType, NullType>, N>: utilities::index_out_of_range<N> { };


    /*
     * forward declaration
     * */
    template <typename TList, typename Type>
    struct has_type;

    template <typename TList, typename Type>
    struct has_type_impl;

    template <typename T, typename U, typename Type>
    struct has_type<TypeList<T, U>, Type>: utilities::invalid_argument<Type>
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



    template <typename TList1, typename TList2>
    struct append_list
    {
        using type = NullType;
    };

    //many to many
    template <typename Cur1, typename Next1, typename Cur2, typename Next2>
    struct append_list<TypeList<Cur1, Next1>, TypeList<Cur2, Next2>>
    {
        using type = TypeList<Cur1, typename append_list<Next1, TypeList<Cur2, Next2>>::type>;
    };

    template <typename Cur, typename Next, typename T>
    struct append_list<TypeList<Cur, Next>, T>
    {
        using type = typename append_list<TypeList<Cur, Next>, SingletonList<T>>::type;
    };

    template <typename Cur, typename Next, typename T>
    struct append_list<T, TypeList<Cur, Next>>
    {
        using type = typename append_list<SingletonList<T>, TypeList<Cur, Next>>::type;
    };

    template <typename Cur, typename Next>
    struct append_list<EmptyList, TypeList<Cur, Next>>
    {
        using type = TypeList<Cur, Next>;
    };

    template <typename Cur, typename Next>
    struct append_list<TypeList<Cur, Next>, EmptyList>
    {
        using type = TypeList<Cur, Next>;
    };

    template <>
    struct append_list<EmptyList, EmptyList>
    {
        using type = EmptyList;
    };

} //implementation
} //tl
