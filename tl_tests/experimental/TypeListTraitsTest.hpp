#pragma once

#include <cstddef>

#include "TLTest.hpp"
#include "TLTypeWrappers.hpp"

#include "source/type_list.hpp"

using namespace TL::testing;

namespace TL {
namespace experimental {


    using zero_list = TypeList<NullType, NullType>;
    using one_list = TypeList<int, NullType>;
    using three_list = TypeList<int, TypeList<int, SingletonList<int>>>;

    void test_length() {
        test_operation<length, TArgs<zero_list, TValue<int, 0>>>();
        test_operation<length, TArgs<one_list, TValue<int, 1>>>();
        test_operation<length, TArgs<three_list, TValue<int, 3>>>();
    }

    void test_empty() {
        test_operation<empty, TArgs<zero_list, TValue<bool, true>>>();
        test_operation<empty, TArgs<one_list, TValue<bool, false>>>();
        test_operation<empty, TArgs<three_list, TValue<bool, false>>>();
    }

    void test_type_count() {
        test_operation<type_count, TArgs<zero_list, int, TValue<int, 0>>>();
        //test_operation<type_count, TArgs<zero_list, TL::experimental::NullType, Value<int, 0>>>();
        test_operation<type_count, TArgs<zero_list, double, TValue<int, 0>>>();
        test_operation<type_count, TArgs<one_list, int, TValue<int, 1>>>();
        test_operation<type_count, TArgs<three_list, int, TValue<int, 3>>>();
        test_operation<type_count, TArgs<three_list, double, TValue<int, 0>>>();
    }

    void test_has_type() {
        test_operation<has_type, TArgs<zero_list, int, TValue<bool, false>>>();
        test_operation<has_type, TArgs<one_list, int, TValue<bool, true>>>();
        test_operation<has_type, TArgs<one_list, double, TValue<bool, false>>>();
        test_operation<has_type, TArgs<three_list, int, TValue<bool, true>>>();
        test_operation<has_type, TArgs<three_list, double, TValue<bool, false>>>();
    }

    template <typename TList, typename Index, typename Result>
    struct test_get_type_tester
    {
        static_assert((std::is_same_v<typename get_type<TList, Index::value>::type, Result>), "get_type");
    };

    void test_get_type() {
        test_operation_with_tester<test_get_type_tester, TArgs<one_list, TValue<std::size_t, 0>, int>>();
        test_operation_with_tester<test_get_type_tester, TArgs<one_list, TValue<std::size_t, 0>, int>>();
        test_operation_with_tester<test_get_type_tester, TArgs<three_list, TValue<std::size_t, 1>, int>>();
        test_operation_with_tester<test_get_type_tester, TArgs<three_list, TValue<std::size_t, 2>, int>>();
    }

} //experimental
}
 //tl
