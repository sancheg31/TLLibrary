#pragma once

#include "tl_test.h"
#include "experimental/TypeList.h"
#include "experimental/TypeListTraits.h"

namespace TL {
namespace experimental {

    void test_length() {
        using test_type = TypeList<int, TypeList<int, TypeList<int, NullType>>>;
        test_operation<length, TArgs<EmptyList, Value<int, 0>>>();
        test_operation<length, TArgs<SingletonList<int>, Value<int, 1>>>();
        test_operation<length, TArgs<test_type, Value<int, 3>>>();
    }

    void test_empty() {
        using test_type = TypeList<int, TypeList<int, TypeList<int, NullType>>>;
        test_operation<empty, TArgs<EmptyList, Value<bool, true>>>();
        test_operation<empty, TArgs<SingletonList<int>, Value<bool, false>>>();
        test_operation<empty, TArgs<test_type, Value<bool, false>>>();
    }

} //experimental
}
 //tl
