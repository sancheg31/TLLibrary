#pragma once


#include <type_traits>

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

template <typename T, typename U>
 inline constexpr int is_same_type = std::is_same_v<T, U>;


} //utilities
} //tl
