#pragma once

#include "source/TLUtility.hpp"
#include "TLTypeWrappers.hpp"

namespace TL {
namespace testing {

    template <typename Operation, typename Result, bool type = traits::has_type_alias_v<Operation>,
                                                    bool type2 = traits::has_type_alias_v<Result>>
    struct test_oper;

    /*
     * Operation returns value
     * Result is T<type, value>
     * Operation's value is equal to Value::value.
     * */
    template <template <class ...> typename Operation, typename T, T V, typename ... Tp>
    struct test_oper<Operation<Tp...>, TValue<T, V>, false, true>
    {
        static_assert((T)(Operation<Tp...>::value) == T(V), "test failed");
    };

    /*
     * Operations returns type
     * Result is a pure type
     * types are the same.
     * */
    template <template <class ...> class Operation, typename Result, typename ... Tp>
    struct test_oper<Operation<Tp...>, Result, true, false>
    {
        static_assert(std::is_same_v<typename Operation<Tp...>::type, Result>, "test failed");
    };

    /*
     * Operation returns value
     *
     * */
    template <template <class ...> class Operation, typename Result, typename ... Tp>
    struct test_oper<Operation<Tp...>, Result, false, false>
    {
        static_assert(std::is_same_v<Operation<Tp...>, Result>, "test failed");
    };

    /*
     * Operation returns type
     * Result is Value<T, V>
     * types are equal
     * */
    template <template <class ...> class Operation, typename T, T V, typename ... Tp>
    struct test_oper<Operation<Tp...>, TValue<T, V>, true, true>
    {
        static_assert(std::is_same_v<Operation<Tp...>, T>, "test failed");
    };


    template <template <class> class Operation, typename ... Tp>
    constexpr void test_operation() {
        ((void)(test_oper<Operation<typename Tp::_1>, typename Tp::_Result>{}), ...);
    }

    template <template <class, class> class Operation, typename ... Tp>
    constexpr void test_operation() {
        ((void)(test_oper<Operation<typename Tp::_1, typename Tp::_2>, typename Tp::_Result>{}), ...);
    }

    template <template <class, class, class> class Operation, typename ... Tp>
    constexpr void test_operation() {
        ((void)(test_oper<Operation<typename Tp::_1, typename Tp::_2, typename Tp::_3>, typename Tp::_Result>{}), ...);
    }


    template <template <class, class> class Operation, typename ... Tp>
    constexpr void test_operation_with_tester() {
        ((void)(Operation<typename Tp::_1, typename Tp::_Result>{}), ...);
    }

    template <template <class, class, class> class Operation, typename ... Tp>
    constexpr void test_operation_with_tester() {
        ((void)(Operation<typename Tp::_1, typename Tp::_2, typename Tp::_Result>{}), ...);
    }

    template <template <class, class, class, class> class Operation, typename ... Tp>
    constexpr void test_operation_with_tester() {
        ((void)(Operation<typename Tp::_1, typename Tp::_2, typename Tp::_3, typename Tp::_Result>{}), ...);
    }

} //testing
} //tl
