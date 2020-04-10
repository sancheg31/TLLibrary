#pragma once


#include <type_traits>

#include "TLNulltype.hpp"

namespace TL {

    template <typename ... Tp>
    struct type_list;

} //tl

namespace TL {
namespace utilities {

    template <class T, class = std::void_t<>>
    struct impl_has_result_type
    {
        enum { value = false };
    };

    template <typename T>
    struct impl_has_result_type<T, std::void_t<typename T::result_type>>
    {
        enum { value = true };
    };

    template <class T, class  = std::void_t<>>
    struct impl_has_value_type
    {
        enum { value = false };
    };

    template <class T>
    struct impl_has_value_type<T, std::void_t<typename T::value_type>>
    {
        enum { value = true };
    };


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

    struct false_argument
    {
        enum { value = 0 };
    };

    struct true_argument
    {
        enum { value = 1 };
    };

    template <typename T, typename U>
    struct is_same: false_argument{ };

    template <typename T>
    struct is_same<T, T>: true_argument { };

    template <typename T, typename U>
    inline constexpr static bool is_same_v = is_same<T, U>::value;

    template <typename IllegalType>
    struct invalid_argument;

    template <typename Illegal>
    struct invalid_argument
    {
    private:
        struct InnerType { };
        static_assert(is_same_v<Illegal, InnerType>, "invalid template argument");
    };

    template <typename ActualType, typename IllegalType>
    struct is_valid_argument;

    template <typename Actual, typename Illegal>
    struct is_valid_argument
    {
        static_assert(!is_same_v<Actual, Illegal>, "invalid template argument");
    };

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

    template <std::size_t N>
    struct index_out_of_range
    {
        static_assert(N == 0, "Index is out of range");
    };

    template <class T>
    struct  has_result_type: public impl_has_result_type<T> { };

    template <typename T>
    struct  has_value_type: public impl_has_value_type<T> { };

    template <class T>
    struct  has_type_alias: public impl_has_type_alias<T> { };

    template <typename T>
    inline constexpr bool has_result_type_v = has_result_type<T>::value;

    template <typename T>
    inline constexpr bool has_value_type_v = has_value_type<T>::value;

    template <typename T>
    inline constexpr bool  has_type_alias_v = has_type_alias<T>::value;


} //utilities
} //tl
