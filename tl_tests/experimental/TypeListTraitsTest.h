#pragma once

#include <cstddef>

#include "tl_test.h"
#include "experimental/TypeList.h"
#include "experimental/TypeListTraits.h"

namespace TL {
namespace experimental {


    using zero_list = TL::experimental::TypeList<TL::experimental::NullType, TL::experimental::NullType>;
    using one_list = TL::experimental::TypeList<int, TL::experimental::NullType>;
    using three_list = TL::experimental::TypeList<int, TypeList<int, SingletonList<int>>>;

    void test_length() {
        test_operation<size, TArgs<zero_list, Value<int, 0>>>();
        test_operation<size, TArgs<one_list, Value<int, 1>>>();
        test_operation<size, TArgs<three_list, Value<int, 3>>>();
    }

    void test_empty() {
        test_operation<empty, TArgs<zero_list, Value<bool, true>>>();
        test_operation<empty, TArgs<one_list, Value<bool, false>>>();
        test_operation<empty, TArgs<three_list, Value<bool, false>>>();
    }

    void test_type_count() {
        test_operation<type_count, TArgs<zero_list, int, Value<int, 0>>>();
        //test_operation<type_count, TArgs<zero_list, TL::experimental::NullType, Value<int, 0>>>();
        test_operation<type_count, TArgs<zero_list, double, Value<int, 0>>>();
        test_operation<type_count, TArgs<one_list, int, Value<int, 1>>>();
        test_operation<type_count, TArgs<three_list, int, Value<int, 3>>>();
        test_operation<type_count, TArgs<three_list, double, Value<int, 0>>>();
    }

    void test_has_type() {
        test_operation<has_type, TArgs<zero_list, int, Value<bool, false>>>();
        test_operation<has_type, TArgs<one_list, int, Value<bool, true>>>();
        test_operation<has_type, TArgs<one_list, double, Value<bool, false>>>();
        test_operation<has_type, TArgs<three_list, int, Value<bool, true>>>();
        test_operation<has_type, TArgs<three_list, double, Value<bool, false>>>();
    }

    template <typename TList, typename Index, typename Result>
    struct test_get_type_tester
    {
        static_assert((std::is_same_v<typename get_type<TList, Index::value>::type, Result>), "get_type");
    };

    void test_get_type() {
        test_operation_with_tester<test_get_type_tester, TArgs<one_list, Value<std::size_t, 0>, int>>();
        test_operation_with_tester<test_get_type_tester, TArgs<one_list, Value<std::size_t, 0>, int>>();
        test_operation_with_tester<test_get_type_tester, TArgs<three_list, Value<std::size_t, 1>, int>>();
        test_operation_with_tester<test_get_type_tester, TArgs<three_list, Value<std::size_t, 2>, int>>();
    }

} //experimental
}
 //tl
