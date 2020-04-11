#pragma once

#include "TLfwd.hpp"
#include "TLTraits.hpp"

namespace TL {
namespace requires {

    /*
     * Forward declaration
     * */
    template <typename TList>
    struct is_type_list;

    template <typename TList>
    struct is_type_list: traits::is_type_list<TList>
    {
        static_assert(is_type_list<TList>::value, "argument is not a type list");
    };

    /*
     * Forward declaration
     * */

    template <typename Type>
    struct is_plain_type;

    template <typename Type>
    struct is_plain_type: traits::is_plain_type<Type>
    {
        static_assert(is_plain_type<Type>::value, "argument is not a plain type");
    };

    /*
     * Forward declaration
     * */
    template <class T>
    struct has_result_type;

    template <class T>
    struct has_result_type: traits::has_result_type<T>
    {
        static_assert(has_result_type<T>::value, "type has no alias named result_type");
    };


    /*
     * Forward declaration
     * */
    template <class T>
    struct has_value_type;

    template <class T>
    struct has_value_type: traits::has_value_type<T>
    {
        static_assert(has_value_type<T>::value, "type has no alias named value_type");
    };


    /*
     * Forward declaration
     * */
    template <class T>
    struct has_type_alias;

    template <class T>
    struct has_type_alias: traits::has_type_alias<T>
    {
        static_assert(has_type_alias<T>::value, "type has no alias named type");
    };

    /*
     * Forward declaration
     * */
    template <class T>
    struct has_value_variable;

    template <class T>
    struct has_value_variable: traits::has_value_variable<T>
    {
        static_assert(has_value_variable<T>::value, "type has no member named value");
    };


    /*
     * Forward declaration
     * */
    template <typename Type>
    struct is_not_nulltype;

    template <typename Type>
    struct is_not_nulltype
    {
        static_assert(!traits::is_same<NullType, Type>::value, "NullType is an invalid template argument");
    };


    /*
     * Forward declaration
     * */
    template <std::size_t I, std::size_t N>
    struct less_than;

    template <std::size_t I, std::size_t N>
    struct less_than
    {
        static_assert(I < N, "index is out of range");
    };

} //requires
} //tl

