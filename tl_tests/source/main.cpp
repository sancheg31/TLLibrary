
#include <iostream>

#include "TLPredefinedTesters.hpp"
#include "TLTest.hpp"
#include "TLTestCase.hpp"

#include "source/type_list.hpp"
#include "source/TLUtility.hpp"
#include "source/TLNulltype.hpp"
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

    using test_list = experimental::type_list<int, int, int>;
    using preffered = experimental::type_list<int, double, int>;
    using actual = typename experimental::replace<test_list, double, 1>::type;

    using list_before = typename experimental::replace<test_list, double, 1>::list_before;
    using list_after = typename experimental::replace<test_list, double, 1>::list_after;

    static_assert(std::is_same_v<actual, preffered>, "uupsie");
    static_assert(std::is_same_v<list_before, experimental::type_list<int>>, "uupsie2");
    static_assert(std::is_same_v<list_after, experimental::type_list<int>>,
            "uupsie3");

    using test_list_2 = experimental::type_list<int, double, char>;
    static_assert(std::is_same_v<typename experimental::reverse<test_list_2>::type,
            experimental::type_list<char, double, int>>, "uupsie4");

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

    test_case<append<empty_list, int>, type_list<int>>();
    test_case<append<type_list<int>, double>, type_list<int, double>>();
    test_case<append<type_list<int, double>, char>, type_list<int, double, char>>();
    test_case<append<type_list<int>, type_list<double>>, type_list<int, double>>();
    test_case<append<type_list<int, double>, type_list<char, double>>, type_list<int, double, char, double>>();
    test_case<append<type_list<>, type_list<>>, type_list<>>();
    test_case<append<type_list<>, type_list<int>>, type_list<int>>();
    test_case<append<type_list<int>, type_list<>>, type_list<int>>();

    test_case<push_back<empty_list, int>, type_list<int>>();
    test_case<push_back<type_list<int>, double>, type_list<int, double>>();
    test_case<push_back<type_list<int, double>, char>, type_list<int, double, char>>();


    test_case<prepend<empty_list, int>, type_list<int>>();
    test_case<prepend<type_list<int>, double>, type_list<double, int>>();
    test_case<prepend<type_list<int, double>, char>, type_list<char, int, double>>();
    test_case<prepend<type_list<int>, type_list<double>>, type_list<double, int>>();
    test_case<prepend<type_list<int, double>, type_list<char, double>>, type_list<char, double, int, double>>();
    test_case<prepend<type_list<>, type_list<>>, type_list<>>();
    test_case<prepend<type_list<>, type_list<int>>, type_list<int>>();
    test_case<prepend<type_list<int>, type_list<>>, type_list<int>>();

    test_case<push_front<empty_list, int>, type_list<int>>();
    test_case<push_front<type_list<int>, double>, type_list<double, int>>();
    test_case<push_front<type_list<int, double>, char>, type_list<char, int, double>>();

    std::cout << "I did it!\n";
    return 0;
}
