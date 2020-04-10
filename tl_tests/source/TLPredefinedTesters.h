#pragma once

#include <type_traits>

#include "source/type_list.h"
#include "source/tl_utilities.h"

namespace TL {
namespace testing {

    template <typename TList, typename Result>
    struct test_has_result_type
    {
        static_assert(utilities::has_result_type<TList>::value == Result::value, "test_has_result_type");
    };

    template <typename TList, typename Result>
    struct test_empty
    {
        static_assert(empty<TList>::value == Result(), "test_empty");
    };

    template <typename TList, typename Result>
    struct test_size
    {
        static_assert((size<TList>() == Result()) && (size(TList{}) == Result()), "test_size");
    };

    template <typename TList, typename Type, typename Result>
    struct test_has_type
    {
        static_assert((has_type<TList, Type>::value == Result()) && (has_type_v<TList, Type> == Result()), "has_type");
    };

    template <typename TList, typename Index, typename Result>
    struct test_get_type
    {
        static_assert((std::is_same_v<get_type_t<TList, Index::value>, Result>) &&
                        (std::is_same_v<typename get_type<TList, Index::value>::type, Result>), "get_type");
    };

    template <typename TList, typename Type, typename Result>
    struct test_type_count
    {
        static_assert(type_count<TList, Type>::value == Result(), "type_count");
    };

    template <typename TList1, typename TList2, typename Result>
    struct test_append
    {
        static_assert(std::is_same_v<append_t<TList1, TList2>, Result>, "test_append");
    };

} //testing
} //TL
