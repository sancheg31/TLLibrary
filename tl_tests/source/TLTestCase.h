#pragma once

#include "TLTypeWrappers.h"
#include "source/tl_utilities.h"
#include "source/type_list.h"


namespace TL {
namespace testing {

    template <class Operation, class Result>
    struct test_case;

    template <class Operation, class Result, bool = utilities::has_type_alias_v<Operation>>
    struct test_case_impl;

    template <class Operation, class Result>
    struct test_case : test_case_impl<Operation, Result> { };

    template <class Operation, class Type, Type Value>
    struct test_case_impl<Operation, TValue<Type, Value>, false>
    {
        constexpr static Type actual = (Type)Operation::value;
        constexpr static Type expected = (Type)Value;
        static_assert(expected == actual, "values are not equal");
    };

    template <class Operation, class Type>
    struct test_case_impl<Operation, Type, true>
    {
        using actual = typename Operation::type;
        using expected = Type;
        static_assert(utilities::is_same<actual, expected>::value, "types are not equal");
    };

} //testing
} //tl
