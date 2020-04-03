#pragma once

#include "tl_fwd.h"
#include "type_list.h"
#include "type_list_impl.h"
#include "tl_utilities.h"

namespace TL {

template <typename T, T N>
struct Value;

template <typename T, T N>
struct Value
{
    using type = T;
    enum { value = N };
    constexpr operator T() { return value; }
};

template <typename ... Tp>
struct TArgs;

template <typename T>
struct TArgs<T>
{
    using _Result = T;
};

template <typename T1, typename T2>
struct TArgs<T1, T2>
{
    using _1 = T1;
    using _Result = T2;
};

template <typename T1, typename T2, typename T3>
struct TArgs<T1, T2, T3>
{
    using _1 = T1;
    using _2 = T2;
    using _Result = T3;
};

template <typename T1, typename T2, typename T3, typename T4>
struct TArgs<T1, T2, T3, T4>
{
    using _1 = T1;
    using _2 = T2;
    using _3 = T3;
    using _Result = T4;
};


template <typename Operation, typename Result, bool type = utilities::has_type_alias_v<Operation>,
                                                bool type2 = utilities::has_type_alias_v<Result>>
struct test_oper;

/*
 * Operation returns value
 * Result is T<type, value>
 * Operation's value is equal to Value::value.
 * */
template <template <class ...> typename Operation, typename T, T V, typename ... Tp>
struct test_oper<Operation<Tp...>, Value<T, V>, false, true>
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
struct test_oper<Operation<Tp...>, Value<T, V>, true, true>
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


} //tl
