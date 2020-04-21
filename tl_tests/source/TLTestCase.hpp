#pragma once

#include "TLTypeWrappers.hpp"
#include "source/TLUtility.hpp"
#include "source/type_list.hpp"


namespace TL {
namespace testing {

    template <class Operation, class Result>
    struct test_case;

    template <class Operation, class Result, bool = traits::has_type_alias_v<Operation>>
    struct test_case_impl;

    template <class Operation, class Result>
    struct test_case : test_case_impl<Operation, Result> { };

    template <class Operation, class Type, Type Value>
    struct test_case_impl<Operation, TValue<Type, Value>, false>
    {
        constexpr static Type actual = (Type)Operation::value;
        constexpr static Type expected = (Type)Value;
        constexpr static bool result = (expected == actual);
        //static_assert(expected == actual, "values are not equal");
    };

    template <class Operation, class Type>
    struct test_case_impl<Operation, Type, true>
    {
        using actual = typename Operation::type;
        using expected = Type;
        constexpr static bool result = std::is_same<expected, actual>::value;
        //static_assert(traits::is_same<actual, expected>::value, "types are not equal");
    };

} //testing
} //tl
