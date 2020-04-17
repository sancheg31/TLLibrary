#pragma once


#include "TLfwd.hpp"
#include "TLIteratorfwd.hpp"

#include <type_traits>

namespace TL {
namespace traits {


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
    template <typename TList>
    struct is_type_list;

    template <typename ... Tp>
    struct is_type_list<type_list<Tp...>>: true_argument { };

    template <typename TList>
    struct is_type_list: false_argument { };


    /*
     * Forward declaration
     * */
    template <typename TList>
    struct is_plain_type;

    template <template <class...> class T, typename ... Tp>
    struct is_plain_type<T<Tp...>>: false_argument { };

    template <typename TList>
    struct is_plain_type: true_argument { };

    /*
     * Forward declaration
     * */
    template <typename TIter>
    struct is_iterator;

    template <typename TList, std::size_t I>
    struct is_iterator<type_list_iterator<TList, I>>: true_argument { };

    template <typename TIter>
    struct is_iterator: false_argument { };

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
    struct has_value_type: public impl_has_value_type<T> { };


    /*
     * Forward declaration
     * */
    template <class T>
    struct has_type_alias;

    template <class T, class = std::void_t<>>
    struct impl_has_type_alias: false_argument { };

    template <class T>
    struct impl_has_type_alias<T, std::void_t<typename T::type>>: true_argument { };

    template <class T>
    struct has_type_alias: public impl_has_type_alias<T> { };

    /*
     * Forward declaration
     * */
    template <class T>
    struct has_value_variable;

    template <class T, class = std::void_t<>>
    struct impl_has_value_variable: false_argument { };

    template <class T>
    struct impl_has_value_variable<T, std::void_t<decltype(T::value)>>: true_argument { };

    template <class T>
    struct has_value_variable: impl_has_value_variable<T> { };


    template <typename TList>
    inline constexpr bool is_type_list_v = is_type_list<TList>::value;

    template <typename Type>
    inline constexpr bool is_plain_type_v = is_plain_type<Type>::value;

    template <typename TIter>
    inline constexpr bool is_iterator_v = is_iterator<TIter>::value;

    template <typename T>
    inline constexpr bool has_result_type_v = has_result_type<T>::value;

    template <typename T>
    inline constexpr bool has_value_type_v = has_value_type<T>::value;

    template <typename T>
    inline constexpr bool has_type_alias_v = has_type_alias<T>::value;

    template <typename T>
    inline constexpr bool has_value_variable_v = has_value_variable<T>::value;

    template <typename T, typename U>
    inline constexpr static bool is_same_v = is_same<T, U>::value;



} //traits
} //tl
