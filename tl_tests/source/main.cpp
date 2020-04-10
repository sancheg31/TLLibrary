
#include <iostream>

#include "TLPredefinedTesters.hpp"
#include "TLTest.hpp"
#include "TLTestCase.hpp"

#include "source/type_list.hpp"
#include "source/TLUtility.hpp"
#include "source/TLNulltype.hpp"


using namespace TL;
using namespace TL::testing;
using namespace TL::utilities;

using integrals = type_list<char, short, int, float, double>;
using doubles = type_list<float, double>;
using doubles_integrals = type_list<float, double, char, short, int, float, double>;
using integrals_doubles = type_list<char, short, int, float, double, float, double>;
using empty_list = type_list<>;

template <typename T>
using is_int = traits::is_same<T, int>;

template <class T>
struct test_true
{
    enum { value = true };
};

template <class T>
struct test_false
{
    enum { value = false };
};

int main()
{
    test_case<length<integrals>, TValue<int, 5>>();
    test_case<length<doubles>, TValue<int, 2>>();
    test_case<length<empty_list>, TValue<int, 0>>();
    test_case<length<doubles_integrals>, TValue<int, 7>>();

    test_case<type_count<integrals, int>, TValue<int, 1>>();
    test_case<type_count<doubles, double>, TValue<int, 1>>();
    test_case<type_count<doubles, float>, TValue<int, 1>>();
    test_case<type_count<doubles, char>, TValue<int, 0>>();
    test_case<type_count<empty_list, double>, TValue<int, 0>>();

    test_case<empty<integrals>, TValue<bool, false>>();
    test_case<empty<doubles>, TValue<bool, false>>();
    test_case<empty<empty_list>, TValue<bool, true>>();
    test_case<empty<type_list<int>>, TValue<bool, false>>();

    test_case<has_type<integrals, char>, TValue<bool, true>>();
    test_case<has_type<integrals, int>, TValue<bool, true>>();
    test_case<has_type<integrals, float>, TValue<bool, true>>();
    test_case<has_type<doubles, float>, TValue<bool, true>>();
    test_case<has_type<doubles, int>, TValue<bool, false>>();
    test_case<has_type<doubles, double>, TValue<bool, true>>();
    test_case<has_type<empty_list, double>, TValue<bool, false>>();

    test_case<get_type<integrals, 0>, char>();
    test_case<get_type<doubles, 0>, float>();
    test_case<get_type<doubles, 1>, double>();
    test_case<get_type<doubles, 0>, float>();
    test_case<get_type<integrals, 4>, double>();

    test_case<all_of<empty_list, test_true>, TValue<bool, true>>();
    test_case<all_of<empty_list, test_false>, TValue<bool, true>>();
    test_case<all_of<empty_list, traits::has_value_type>, TValue<bool, true>>();
    test_case<all_of<integrals, test_true>, TValue<bool, true>>();
    test_case<all_of<integrals, test_false>, TValue<bool, false>>();
    test_case<all_of<integrals, traits::has_value_type>, TValue<bool, false>>();
    test_case<all_of<integrals, is_int>, TValue<bool, false>>();
    test_case<all_of<doubles, is_int>, TValue<bool, false>>();


    test_case<none_of<empty_list, test_true>, TValue<bool, true>>();
    test_case<none_of<empty_list, test_false>, TValue<bool, true>>();
    test_case<none_of<integrals, test_false>, TValue<bool, true>>();
    test_case<none_of<integrals, traits::has_value_type>, TValue<bool, true>>();
    test_case<none_of<integrals, is_int>, TValue<bool, false>>();
    test_case<none_of<doubles, is_int>, TValue<bool, true>>();

    test_case<any_of<empty_list, test_true>, TValue<bool, false>>();
    test_case<any_of<empty_list, test_false>, TValue<bool, false>>();
    test_case<any_of<integrals, test_true>, TValue<bool, true>>();
    test_case<any_of<integrals, test_false>, TValue<bool, false>>();
    test_case<any_of<integrals, is_int>, TValue<bool, true>>();
    test_case<any_of<doubles, is_int>, TValue<bool, false>>();
/*
    TL::test_operation<
        utilities::has_result_type,
        TArgs<integrals, TValue<bool, true>>,
        TArgs<double, TValue<bool, false>>,
        TArgs<doubles, TValue<bool, true>>,
        TArgs<empty_list, TValue<bool, true>>,
        TArgs<Value<int, 0>, Value<bool, false>>
    >();

    TL::test_operation<
        utilities::has_type_alias,
        TArgs<integrals, TValue<bool, false>>,
        TArgs<double, TValue<bool, false>>,
        TArgs<doubles, TValue<bool, false>>,
        TArgs<Value<bool, true>, TValue<bool, true>>
    >();

    TL::test_operation<
        has_type,
        TArgs<integrals, int, TValue<bool, false>>,
        TArgs<doubles, double, TValue<bool, true>>,
        TArgs<empty_list, double, Value<bool, false>>
    >();

    TL::test_operation_with_tester<
        test_size,
        TArgs<integrals, TValue<int, 5>>,
        TArgs<doubles, Value<int, 1>>,
        TArgs<empty_list, Value<int, 0>>
    >();

    TL::test_operation<
        empty,
        TArgs<integrals, TValue<bool, false>>,
        TArgs<doubles, Value<bool, false>>,
        TArgs<empty_list, Value<bool, true>>
    >();

    TL::test_operation_with_tester<
        test_get_type,
        TArgs<integrals, TValue<int, 0>, char>,
        TArgs<doubles, Value<int, 0>, double>,
        TArgs<integrals, Value<int, 1>, short>,
        TArgs<integrals, Value<int, 2>, int>
    >();

    TL::test_operation<
        type_count,
        TArgs<integrals, int, TValue<int, 1>>,
        TArgs<integrals, std::string, Value<int, 0>>,
        TArgs<doubles, double, Value<int, 1>>,
        TArgs<doubles, int, Value<int, 0>>,
        TArgs<empty_list, int, Value<int, 0>>,
        TArgs<empty_list, double, Value<int, 0>>
    >();
*/
    std::cout << "I did it!\n";
    return 0;
}
