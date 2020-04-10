#pragma once

#include "TLfwd.hpp"

#include <type_traits>

namespace TL {
namespace utilities {

    /*
     * Forward declaration
     * */
    struct true_argument;

    struct true_argument
    {
        enum { value = true };
    };


    /*
     * Forward declaration
     * */
    struct false_argument;

    struct false_argument
    {
        enum { value = false };
    };


    /*
     * Forward declaration
     * */
    template <class T>
    struct has_result_type;

    template <class T, class = std::void_t<>>
    struct impl_has_result_type: false_argument { };

    template <typename T>
    struct impl_has_result_type<T, std::void_t<typename T::result_type>>: true_argument { };

    template <class T>
    struct has_result_type: impl_has_result_type<T> { };

    /*
     * Forward declaration
     * */
    template <class T>
    struct has_value_type;

    template <class T, class  = std::void_t<>>
    struct impl_has_value_type: false_argument { };

    template <class T>
    struct impl_has_value_type<T, std::void_t<typename T::value_type>>: true_argument { };

    template <typename T>
    struct  has_value_type: public impl_has_value_type<T> { };


    /*
     * Forward declaration
     * */
    template <class T>
    struct has_type_alias;

    template <class T, class = std::void_t<>>
    struct impl_has_type_alias
    {
        enum { value = false };
    };

    template <class T>
    struct impl_has_type_alias<T, std::void_t<typename T::type>>
    {
        enum { value = true };
    };

    template <class T>
    struct  has_type_alias: public impl_has_type_alias<T> { };

    /*
     * Forward declaration
     * */
    template <typename T, typename U>
    struct is_same;

    template <typename T, typename U>
    struct is_same: false_argument{ };

    template <typename T>
    struct is_same<T, T>: true_argument { };


    /*
     * Forward declaration
     * */
    template <typename IllegalType>
    struct invalid_argument;

    template <typename Illegal>
    struct invalid_argument
    {
    private:
        struct InnerType { };
        static_assert(is_same<Illegal, InnerType>::value, "invalid template argument");
    };


    /*
     * Forward declaration
     * */
    template <typename ActualType, typename IllegalType>
    struct is_valid_argument;

    template <typename Actual, typename Illegal>
    struct is_valid_argument
    {
        static_assert(!is_same<Actual, Illegal>::value, "invalid template argument");
    };


    /*
     * Forward declaration
     * */
    template <typename Type>
    struct type_or_list;

    template <typename Type>
    struct type_or_list
    {
        using result = Type;
    };

    template <typename ... Tp>
    struct type_or_list<type_list<Tp...>>
    {
        using result = typename type_list<Tp...>::result_type;
    };


    /*
     * Forward declaration
     * */
    template <std::size_t N>
    struct index_out_of_range;

    template <std::size_t N>
    struct index_out_of_range
    {
        static_assert(N == 0, "Index is out of range");
    };

    template <typename T>
    inline constexpr bool has_result_type_v = has_result_type<T>::value;

    template <typename T>
    inline constexpr bool has_value_type_v = has_value_type<T>::value;

    template <typename T>
    inline constexpr bool  has_type_alias_v = has_type_alias<T>::value;

    template <typename T, typename U>
    inline constexpr static bool is_same_v = is_same<T, U>::value;

} //utilities
} //tl
