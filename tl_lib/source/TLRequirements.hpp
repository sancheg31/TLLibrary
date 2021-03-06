#pragma once

#include "TLfwd.hpp"
#include "TLTraits.hpp"

namespace TL {
namespace requires {


    template <typename TList>
    struct is_type_list<TList>
    {
        static_assert(traits::is_type_list<TList>::value, "argument is not a type list");
    };

    template <typename ... TLists>
    struct is_type_list {
        static_assert(((..., is_type_list<TLists>{}), true), "argument is not a type list");
    };

    template <typename TList>
    struct is_index_list<IndexList> {
        static_assert()
    };

    template <typename ... TLists>
    struct is_index_list {

    }

    template <typename Type>
    struct is_not_nulltype<Type>
    {
        static_assert(!traits::is_same<NullType, Type>::value, "NullType is an invalid template argument");
    };

    template <typename ... Types>
    struct is_not_nulltype {
        static_assert(((... && is_not_nulltype<Types>{}), true), "NullType is an invalid template argument");
    };

    template <typename TIter>
    struct is_iterator<TIter>
    {
        static_assert(traits::is_iterator<TIter>::value, "argument is not an iterator");
    };

    template <typename ... TIters>
    struct is_iterator {
        static_assert(((..., is_iterator<TIters>{}), true), "argument is not an iterator");
    };

    template <typename T, typename U>
    struct is_same<T, U>
    {
        static_assert(traits::is_same<T, U>::value, "types are not same");
    };

    template <typename T, typename ...Types>
    struct is_same<T, Types...>
    {
        static_assert(((..., is_same<T, Types>{}), true), "types are not same");
    };

    template <class T>
    struct has_result_type
    {
        static_assert(traits::has_result_type<T>::value, "type has no alias named result_type");
    };

    template <class T>
    struct has_value_type
    {
        static_assert(traits::has_value_type<T>::value, "type has no alias named value_type");
    };

    template <class T>
    struct has_type_alias
    {
        static_assert(traits::has_type_alias<T>::value, "type has no alias named type");
    };

    template <class T>
    struct has_value_variable
    {
        static_assert(traits::has_value_variable<T>::value, "type has no member named value");
    };

    template <std::size_t X, std::size_t Y, template <class> class Relation>
    struct satisfies_relation
    {
        static_assert(Relation<std::size_t>{}(X, Y), "relation is not satisfied");
    };

    template <auto X, auto Y>
    struct less: satisfies_relation<X, Y, std::less> { };

    template <auto X, auto Y>
    struct greater: satisfies_relation<X, Y, std::greater> { };

    template <auto X, auto Y>
    struct less_equal: satisfies_relation<X, Y, std::less_equal> { };

    template <auto X, auto Y>
    struct greater_equal: satisfies_relation<X, Y, std::greater_equal> { };

    template <auto X, auto Y>
    struct equal_to: satisfies_relation<X, Y, std::equal_to> { };

    template <auto X, auto Y>
    struct not_equal_to: satisfies_relation<X, Y, std::not_equal_to> { };

    template <auto X, auto Lower, auto Upper>
    struct in_range_exclusive: greater<X, Lower>, less<X, Upper> { };

    template <auto X, auto Lower, auto Upper>
    struct in_range_inclusive: greater_equal<X, Lower>, less_equal<X, Upper>  { };


} //requires
} //tl


