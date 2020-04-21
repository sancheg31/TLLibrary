
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <string>
#include <memory>

#include <gtest/gtest.h>

#include "TLPredefinedTesters.hpp"
#include "TLTest.hpp"
#include "TLTestCase.hpp"
#include "TLTypeIteratorTests.hpp"

#include "source/type_list.hpp"
#include "source/TLUtility.hpp"
#include "source/TLNullType.hpp"
#include "experimental/ExpandingPack.h"


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
/*
    test_case<type_count<integrals, int>, TValue<int, 1>>();
    test_case<type_count<doubles, double>, TValue<int, 1>>();
    test_case<type_count<doubles, float>, TValue<int, 1>>();
    test_case<type_count<doubles, char>, TValue<int, 0>>();
    test_case<type_count<empty_list, double>, TValue<int, 0>>();
*/

    /*
    test_case<find_type<integrals, is_int>, int>();
    test_case<find_type<integrals, test_true>, char>();
    test_case<find_type<doubles, test_false>, NullType>();
    test_case<find_type<doubles, is_int>, NullType>();
    test_case<find_type<empty_list, test_true>, NullType>();
    test_case<find_type<empty_list, test_false>, NullType>();


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
    */

    ::testing::InitGoogleTest();

    std::cout << "I did it!\n";
    return RUN_ALL_TESTS();
}
