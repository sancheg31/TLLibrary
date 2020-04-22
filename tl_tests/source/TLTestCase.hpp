#pragma once

#include "TLTypeWrappers.hpp"
#include "source/TLUtility.hpp"
#include "source/type_list.hpp"


namespace TL {
namespace testing {

    template <class... Ts>
    struct make_void
    {
        using type = void;
    };

    template <class... Ts>
    using void_t = typename make_void<Ts...>::type;

    template <class Operation, class Result>
    bool test_case();

    template <class Operation, auto Value>
    bool test_case();

    template <typename TOperation, typename TResult, class = void_t<>>
    struct test_case_impl;



    template <class TOperation, class TResult>
    bool test_case() {
        return test_case_impl<TOperation, TResult>::result;
    }

    template <class TOperation, auto Value>
    bool test_case() {
        return test_case_impl<TOperation, TValue<Value>>::result;
    }


    template <class Operation, class Type>
    struct test_case_impl<Operation, Type, void_t<typename Operation::type>>
    {
        using actual = typename Operation::type;
        using expected = Type;
        constexpr static bool result = std::is_same<expected, actual>::value;
    };

    template <class TOperation, class TResult>
    struct test_case_impl<TOperation, TResult, void_t<typename TOperation::result>>
    {
        using actual = typename TOperation::result;
        using expected = TResult;
        constexpr static bool result = std::is_same<expected, actual>::value;
    };

    template <class TOperation, auto Value>
    struct test_case_impl<TOperation, TValue<Value>, void_t<decltype(TOperation::value)>>
    {
        constexpr static bool result = (TOperation::value == Value);
    };

    template <class TOperation, auto Value>
    struct test_case_impl<TOperation, TValue<Value>, void_t<decltype(TOperation::result)>>
    {
        constexpr static bool result = (TOperation::result = Value);
    };



} //testing
} //tl
