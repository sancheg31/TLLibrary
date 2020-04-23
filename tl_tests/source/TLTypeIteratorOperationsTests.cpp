#include "TLTypeIteratorOperationsTests.hpp"

namespace TL {
namespace testing {

TEST_F(TLTypeIteratorOperationsTests, AdvanceHasNestedTypeResult) {
    EXPECT_TRUE((has_type_result_v<advance<type_iterator<list_1_2, 0>, 1>>));
    EXPECT_TRUE((has_type_result_v<advance<type_iterator<list_1, 1>, -1>>));
    EXPECT_TRUE((has_type_result_v<advance<type_iterator<list_1_2_3, 3>, 0>>));
}

TEST_F(TLTypeIteratorOperationsTests, AdvanceReturnsCorrectIterator) {
    EXPECT_TRUE((test_case<advance<type_iterator<list_1_2, 0>, 1>, type_iterator<list_1_2, 1>>()));
    EXPECT_TRUE((test_case<advance<type_iterator<list_1_1_1, 3>, -3>, type_iterator<list_1_1_1, 0>>()));
    EXPECT_TRUE((test_case<advance<type_iterator<list_1_2_3, 3>, 0>, type_iterator<list_1_2_3, 3>>()));
    EXPECT_TRUE((test_case<advance<type_iterator<list_1_2, 0>, 0>, type_iterator<list_1_2, 0>>()));
    EXPECT_TRUE((test_case<advance<type_iterator<list_1_2_3, 1>, 1>, type_iterator<list_1_2_3, 2>>()));
    EXPECT_TRUE((test_case<advance<type_iterator<list_1_2_1, 2>, -1>, type_iterator<list_1_2_1, 1>>()));
}

TEST_F(TLTypeIteratorOperationsTests, DistanceHasNestedValueResult) {
    EXPECT_TRUE((has_value_result_v<distance<type_iterator<list_1_2, 0>, type_iterator<list_1_2, 1>>>));
    EXPECT_TRUE((has_value_result_v<distance<type_iterator<list_1_2_3, 3>, type_iterator<list_1_2_3, 0>>>));
    EXPECT_TRUE((has_value_result_v<distance<type_iterator<list_1_1_1, 1>, type_iterator<list_1_1_1, 1>>>));
}

TEST_F(TLTypeIteratorOperationsTests, DistanceReturnsCorrectValue) {
    EXPECT_EQ(1, (distance<type_iterator<list_1_2, 0>, type_iterator<list_1_2, 1>>::result));
    EXPECT_EQ(3, (distance<type_iterator<list_1_2_3, 3>, type_iterator<list_1_2_3, 0>>::result));
    EXPECT_EQ(0, (distance<type_iterator<list_1_1_1, 1>, type_iterator<list_1_1_1, 1>>::result));
    EXPECT_EQ(2, (distance<type_iterator<list_1_1_1, 3>, type_iterator<list_1_1_1, 1>>::result));
}


TEST_F(TLTypeIteratorOperationsTests, BeginHasNestedTypeResult) {
    EXPECT_TRUE((has_type_result_v<begin<empty_list>>));
    EXPECT_TRUE((has_type_result_v<begin<list_1_2>>));
    EXPECT_TRUE((has_type_result_v<begin<list_1_1_1>>));
}

TEST_F(TLTypeIteratorOperationsTests, BeginReturnsCorrectIterator) {
    EXPECT_TRUE((test_case<begin<empty_list>, type_iterator<empty_list, 0>>()));
    EXPECT_TRUE((test_case<begin<list_2>, type_iterator<list_2, 0>>()));
    EXPECT_TRUE((test_case<begin<list_1_2>, type_iterator<list_1_2, 0>>()));
    EXPECT_TRUE((test_case<begin<list_1_2_1>, type_iterator<list_1_2_1, 0>>()));
}

TEST_F(TLTypeIteratorOperationsTests, EndHasNestedTypeResult) {
    EXPECT_TRUE((has_type_result_v<end<empty_list>>));
    EXPECT_TRUE((has_type_result_v<end<list_1_2>>));
    EXPECT_TRUE((has_type_result_v<end<list_1_1_1>>));
}

TEST_F(TLTypeIteratorOperationsTests, EndReturnsCorrectIterator) {
    EXPECT_TRUE((test_case<end<empty_list>, type_iterator<empty_list, 0>>()));
    EXPECT_TRUE((test_case<end<list_1>, type_iterator<list_1, 1>>()));
    EXPECT_TRUE((test_case<end<list_1_2>, type_iterator<list_1_2, 2>>()));
    EXPECT_TRUE((test_case<end<list_1_2_1>, type_iterator<list_1_2_1, 3>>()));
}

} //testing
} //tl

