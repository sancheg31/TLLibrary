#pragma once

#include <type_traits>
#include "type_list.hpp"

namespace TL {

#define TL_HAS_NESTED_VALUE(name) \
    template <typename T, class = std::void_t<>> \
    struct has_value_##name##_property_impl { \
        enum { value = false }; \
    }; \
    template <typename T> \
    struct has_value_##name##_property_impl<T, std::void_t<decltype(T::value)>> { \
        enum { value = true }; \
    }; \
    template <typename T> \
    struct has_value_##name: has_value_##name##_property_impl<T> { }; \
    template <typename T> \
    static constexpr bool has_value_##name##_v = has_value_##name<T>::value;

#define TL_HAS_NESTED_TEMPLATE_VALUE(name) \
    template <typename T, typename ... Tp> \
    struct has_template_value_##name##_property_impl \
    { \
        template <typename U = T, class = std::void_t<>> \
        struct has_inner \
        { enum { value = false }; }; \
        template <typename U> \
        struct has_inner<U, std::void_t<decltype(U::template value<Tp...>)>>  \
        { enum { value = true }; }; \
        enum { value = has_inner<>::value }; \
    }; \
    template <typename T, typename ... Tp> \
    struct has_value_##name: has_template_value_##name##_property_impl<T, Tp...> { }; \
    template <typename T, typename ... Tp> \
    static constexpr bool has_value_##name##_v = has_value_##name<T, Tp...>::value;


#define TL_HAS_TYPE(name) \
    template <typename T, class = std::void_t<>> \
    struct has_type_##name##_property_impl { \
        enum { value = false };  \
    }; \
    template <typename T> \
    struct has_type_##name##_property_impl<T, std::void_t<typename T::name>> { \
        enum { value = true }; \
    }; \
    template <typename T> \
    struct has_type_##name: has_type_##name##_property_impl<T> { }; \
    template <typename T> \
    static constexpr bool has_type_##name##_v = has_type_##name<T>::value;

#define TL_HAS_TEMPLATE_TYPE(name) \
    template <typename T, typename ... Tp> \
    struct has_template_type_##name##_property_impl \
    { \
        template <typename U = T, class = std::void_t<>> \
        struct has_inner \
        { enum { value = false }; }; \
        template <typename U> \
        struct has_inner<U, std::void_t<typename U::template type<Tp...>>>  \
        { enum { value = true }; }; \
        enum { value = has_inner<>::value }; \
    }; \
    template <typename T, typename ... Tp> \
    struct has_type_##name: has_template_type_##name##_property_impl<T, Tp...> { }; \
    template <typename T, typename ... Tp> \
    static constexpr bool has_type_##name##_v = has_type_##name<T, Tp...>::value;

} //tl
