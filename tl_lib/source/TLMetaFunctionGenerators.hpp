#pragma once

#include <type_traits>

#define GENERATE_VALUE_PROPERTY_METAFUNCTION(name) \
    template <typename T, class = std::void_t<>> \
    struct has_value_##name##_property_impl { \
        enum { value = false }; \
    }; \
    template <typename T> \
    struct has_value_##name##_property_impl<T, std::void_t<decltype(T::value)>> { \
        enum { value = true }; \
    }; \
    template <typename T> \
    static constexpr bool has_##name##_property = has_value_##name##_property_impl<T>::value;


#define GENERATE_TEMPLATE_VALUE_PROPERTY_METAFUNCTION(name) \
    template <typename T, class = std::void_t<>> \
    struct has_template_value_##name##_property_impl { \
        enum { value = false }; \
    }; \
    template <typename T> \
    struct has_template_value_##name##_property_impl<T, std::void_t<decltype(T::value)>> { \
        enum { value = true }; \
    }; \
    template <typename T> \
    static constexpr bool has_##name##_property = has_template_value_##name##_property_impl<T>::value;

#define GENERATE_TYPE_PROPERTY_METAFUNCTION(name) \
    template <typename T, class = std::void_t<>> \
    struct has_type_##name##_property_impl { \
        enum { value = false };  \
    }; \
    template <typename T> \
    struct has_type_##name##_property_impl<T, std::void_t<typename T::name>> { \
        enum { value = true }; \
    }; \
    template <typename T> \
    static constexpr bool has_##name##_property = has_type_##name##_property_impl<T>::value;


#define GENERATE_TEMPLATE_TYPE_PROPERTY_METAFUNCTION(name) \
    template <typename T, typename U, class = std::void_t<>> \
    struct has_template_type_##name##_property_impl { \
        enum { value = false }; \
    }; \
    template <typename T, typename U> \
    struct has_template_type_##name##_property_impl<T, U, std::void_t<typename T::template name<U>>> { \
        enum { value = true }; \
    }; \
    template <typename T, typename U = void> \
    static constexpr bool has_##name##_property = has_template_type_##name##_property_impl<T, U>::value;

