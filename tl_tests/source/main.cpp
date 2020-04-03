
#include <iostream>

#include "type_list.h"
#include "tl_testers.h"
#include "tl_test.h"
#include "tl_utilities.h"

using namespace TL;
using namespace TL::testers;
using namespace TL::utilities;

using integrals = type_list<char, short, int, float, double>;
using doubles = type_list<double>;
using doubles_integrals = type_list<double, char, short, int, float, double>;
using integrals_doubles = type_list<char, short, int, float, double, double>;
using empty_list = type_list<>;

int main()
{
    TL::test_operation<
        utilities::has_result_type,
        TArgs<integrals, Value<bool, true>>,
        TArgs<double, Value<bool, false>>,
        TArgs<doubles, Value<bool, true>>,
        TArgs<empty_list, Value<bool, true>>,
        TArgs<Value<int, 0>, Value<bool, false>>
    >();

    TL::test_operation<
        utilities::has_type_alias,
        TArgs<integrals, Value<bool, false>>,
        TArgs<double, Value<bool, false>>,
        TArgs<doubles, Value<bool, false>>,
        TArgs<Value<bool, true>, Value<bool, true>>
    >();

    TL::test_operation<
        has_type,
        TArgs<integrals, int, Value<bool, true>>,
        TArgs<doubles, double, Value<bool, true>>,
        TArgs<empty_list, double, Value<bool, false>>,
        TArgs<empty_list, __NullType, Value<bool, false>>
    >();

    TL::test_operation_with_tester<
        test_has_result_type,
        TArgs<integrals, Value<bool, true>>,
        TArgs<doubles, Value<bool, true>>,
        TArgs<empty_list, Value<bool, true>>,
        TArgs<double, Value<bool,false>>
    >();

    TL::test_operation_with_tester<
        test_size,
        TArgs<integrals, Value<int, 5>>,
        TArgs<doubles, Value<int, 1>>,
        TArgs<empty_list, Value<int, 0>>
    >();

    TL::test_operation<
        empty,
        TArgs<integrals, Value<bool, false>>,
        TArgs<doubles, Value<bool, false>>,
        TArgs<empty_list, Value<bool, true>>
    >();

    TL::test_operation_with_tester<
        test_get_type,
        TArgs<integrals, Value<int, 0>, char>,
        TArgs<doubles, Value<int, 0>, double>,
        TArgs<integrals, Value<int, 1>, short>,
        TArgs<integrals, Value<int, 2>, int>
    >();

    TL::test_operation<
        type_count,
        TArgs<integrals, int, Value<int, 1>>,
        TArgs<integrals, std::string, Value<int, 0>>,
        TArgs<doubles, double, Value<int, 1>>,
        TArgs<doubles, int, Value<int, 0>>,
        TArgs<empty_list, int, Value<int, 0>>,
        TArgs<empty_list, double, Value<int, 0>>
    >();

    TL::test_operation<
        append,
        TArgs<empty_list, empty_list, empty_list>,
        TArgs<empty_list, doubles, doubles>,
        TArgs<doubles, empty_list, doubles>,
        TArgs<empty_list, integrals, integrals>,
        TArgs<integrals, empty_list, integrals>,
        TArgs<empty_list, double, doubles>,
        TArgs<double, empty_list, doubles>,
        TArgs<integrals, doubles, integrals_doubles>,
        TArgs<doubles, integrals, doubles_integrals>
    >();
    std::cout << "I did it!\n";
    return 0;
}
