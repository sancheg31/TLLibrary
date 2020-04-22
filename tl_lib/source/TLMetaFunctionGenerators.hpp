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
    struct has_value_##name##_property_impl<T, std::void_t<decltype(T::name)>> { \
        enum { value = true }; \
    }; \
    template <typename T> \
    struct has_value_##name: has_value_##name##_property_impl<T> { }; \
    template <typename T> \
    static constexpr bool has_value_##name##_v = has_value_##name<T>::value;

namespace testing {
    struct InnerTestValue1 { enum {test_value_1 = true }; };
    TL_HAS_NESTED_VALUE(test_value_1);
    static_assert(has_value_test_value_1<int>::value == false, "TL_HAS_NESTED_VALUE");
    static_assert(has_value_test_value_1<InnerTestValue1>::value == true, "TL_HAS_NESTED_VALUE");
    static_assert(has_value_test_value_1_v<int> == has_value_test_value_1<int>::value, "TL_HAS_NESTED_VALUE");
}

#define TL_HAS_NESTED_TEMPLATE_VALUE(name) \
    template <typename T, typename ... Tp> \
    struct has_template_value_##name##_property_impl \
    { \
        template <typename U = T, class = std::void_t<>> \
        struct has_inner \
        { enum { value = false }; }; \
        template <typename U> \
        struct has_inner<U, std::void_t<decltype(U::template name<Tp...>)>>  \
        { enum { value = true }; }; \
        enum { value = has_inner<>::value }; \
    }; \
    template <typename T, typename ... Tp> \
    struct has_value_##name: has_template_value_##name##_property_impl<T, Tp...> { }; \
    template <typename T, typename ... Tp> \
    static constexpr bool has_value_##name##_v = has_value_##name<T, Tp...>::value;

namespace testing {
    struct InnerTestValue2 {
        template <typename T>
        inline static constexpr bool test_value_2 = true;
    };
    struct InnerType { };
    TL_HAS_NESTED_TEMPLATE_VALUE(test_value_2);
    static_assert(has_value_test_value_2<int, int>::value == false, "TL_HAS_NESTED_TEMPLATE_VALUE");
    static_assert(has_value_test_value_2<InnerTestValue2, int>::value == true, "TL_HAS_NESTED_TEMPLATE_VALUE");
    static_assert(has_value_test_value_2<InnerTestValue2, InnerType>::value == true, "TL_HAS_NESTED_TEMPLATE_VALUE");
    static_assert(has_value_test_value_2<InnerTestValue2>::value == false, "TL_HAS_NESTED_TEMPLATE_VALUE");
    static_assert(has_value_test_value_2<int>::value == false, "TL_HAS_NESTED_TEMPLATE_VALUE");
}

#define TL_HAS_NESTED_TYPE(name) \
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

namespace testing {
    struct InnerTestType1 {
        using test_type_1 = void;
    };
    TL_HAS_NESTED_TYPE(test_type_1)
    static_assert(has_type_test_type_1<InnerTestType1>::value == true, "TL_HAS_NESTED_TYPE");
    static_assert(has_type_test_type_1_v<InnerTestType1> ==
                    has_type_test_type_1<InnerTestType1>::value, "TL_HAS_NESTED_TYPE");
    static_assert(has_type_test_type_1<int>::value == false, "TL_HAS_NESTED_TYPE");
}

#define TL_HAS_NESTED_TEMPLATE_TYPE(name) \
    template <typename T, typename ... Tp> \
    struct has_template_type_##name##_property_impl \
    { \
        template <typename U = T, class = std::void_t<>> \
        struct has_inner \
        { enum { value = false }; }; \
        template <typename U> \
        struct has_inner<U, std::void_t<typename U::template name<Tp...>>>  \
        { enum { value = true }; }; \
        enum { value = has_inner<>::value }; \
    }; \
    template <typename T, typename ... Tp> \
    struct has_type_##name: has_template_type_##name##_property_impl<T, Tp...> { }; \
    template <typename T, typename ... Tp> \
    static constexpr bool has_type_##name##_v = has_type_##name<T, Tp...>::value;

namespace testing {
    struct InnerTestType2 {
        template <typename T, typename U>
        using test_type_2 = void;
    };
    TL_HAS_NESTED_TEMPLATE_TYPE(test_type_2)
    static_assert(has_type_test_type_2<InnerTestType2, int, double>::value == true, "TL_HAS_NESTED_TEMPLATE_TYPE");
    static_assert(has_type_test_type_2<InnerTestType2, int>::value == false, "TL_HAS_NESTED_TEMPLATE_TYPE");
    static_assert(has_type_test_type_2<InnerTestType2>::value == false, "TL_HAS_NESTED_TEMPLATE_TYPE");
    static_assert(has_type_test_type_2_v<InnerTestType2> ==
                    has_type_test_type_2<InnerTestType2>::value, "TL_HAS_NESTED_TEMPLATE_TYPE");
    static_assert(has_type_test_type_2<int>::value == false, "TL_HAS_NESTED_TEMPLATE_TYPE");
    static_assert(has_type_test_type_2<int, void, void>::value == false, "TL_HAS_NESTED_TEMPLATE_TYPE");
}
} //tl
