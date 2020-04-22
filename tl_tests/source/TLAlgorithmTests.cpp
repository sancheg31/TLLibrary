
#include "TLAlgorithmTests.hpp"
#include "TLTestCase.hpp"

#include "source/TLAlgorithm.hpp"
#include "source/TLTypeIterator.hpp"
#include "source/type_list.hpp"



namespace TL {
namespace testing {


TEST_F(TLAlgorithmTests, AllOfHasNestedResultValue) {
    EXPECT_TRUE((has_value_result_v<all_of<iterator_begin<list_1>, iterator_end<list_1>, as_inner_1>>));
    EXPECT_TRUE((has_value_result_v<all_of<iterator_begin<empty_list>, iterator_end<empty_list>, true_predicate>>));
    EXPECT_TRUE((has_value_result_v<all_of<iterator_begin<list_1_2_3>, iterator_end<list_1_2_3>, false_predicate>>));
}

TEST_F(TLAlgorithmTests, AllOfEmptyListReturnsTrue) {
    EXPECT_TRUE((all_of<iterator_begin<empty_list>, iterator_end<empty_list>, true_predicate>::result));
    EXPECT_TRUE((all_of<iterator_begin<empty_list>, iterator_end<empty_list>, false_predicate>::result));
    EXPECT_TRUE((all_of<iterator_begin<empty_list>, iterator_end<empty_list>, as_inner_1>::result));
}

TEST_F(TLAlgorithmTests, AllOfPredOnceFalseReturnsFalse) {
    EXPECT_FALSE((all_of<iterator_begin<list_1_2_3>, iterator_end<list_1_2_3>, false_predicate>::result));
    EXPECT_FALSE((all_of<iterator_begin<list_1_2>, iterator_end<list_1_2>, as_inner_1>::result));
}

TEST_F(TLAlgorithmTests, AllOfPredAlwaysTrueReturnsTrue) {
    EXPECT_TRUE((all_of<iterator_begin<list_1>, iterator_end<list_1>, true_predicate>::result));
    EXPECT_TRUE((all_of<iterator_begin<list_1_2>, iterator_next<iterator_begin<list_1_2>>, as_inner_1>::result));

    EXPECT_TRUE((all_of<iterator_begin<list_1_2>, iterator_next<iterator_begin<list_1_2>>, as_inner_1>::result));
}



TEST_F(TLAlgorithmTests, AnyOfHasNestedResultValue) {
    EXPECT_TRUE((has_value_result_v<any_of<iterator_begin<list_1>, iterator_end<list_1>, as_inner_1>>));
    EXPECT_TRUE((has_value_result_v<any_of<iterator_begin<empty_list>, iterator_end<empty_list>, true_predicate>>));
    EXPECT_TRUE((has_value_result_v<any_of<iterator_begin<list_1_2_3>, iterator_end<list_1_2_3>, false_predicate>>));
}

TEST_F(TLAlgorithmTests, AnyOfEmptyListReturnsFalse) {
    EXPECT_FALSE((any_of<iterator_begin<empty_list>, iterator_end<empty_list>, true_predicate>::result));
    EXPECT_FALSE((any_of<iterator_begin<empty_list>, iterator_end<empty_list>, false_predicate>::result));
    EXPECT_FALSE((any_of<iterator_begin<empty_list>, iterator_end<empty_list>, as_inner_1>::result));
}

TEST_F(TLAlgorithmTests, AnyOfPredAlwaysFalseReturnsFalse) {
    EXPECT_FALSE((any_of<iterator_begin<list_1_2_3>, iterator_end<list_1_2_3>, false_predicate>::result));
    EXPECT_FALSE((any_of<iterator_begin<list_1_2>, iterator_end<list_1_2>, as_inner_3>::result));
    EXPECT_FALSE((any_of<iterator_next<iterator_begin<list_1_2>>, iterator_end<list_1_2>, as_inner_1>::result));
}

TEST_F(TLAlgorithmTests, AnyOfPredOnceTrueReturnsTrue) {
    EXPECT_TRUE((any_of<iterator_begin<list_1>, iterator_end<list_1>, true_predicate>::result));
    EXPECT_TRUE((any_of<iterator_begin<list_1_1_1>, iterator_end<list_1_1_1>, as_inner_1>::result));
    EXPECT_TRUE((any_of<iterator_next<iterator_begin<list_1_2>>, iterator_end<list_1_2>, as_inner_2>::result));
}



TEST_F(TLAlgorithmTests, NoneOfHasNestedResultValue) {
    EXPECT_TRUE((none_of<iterator_begin<empty_list>, iterator_end<empty_list>, true_predicate>::result));
    EXPECT_TRUE((none_of<iterator_begin<empty_list>, iterator_end<empty_list>, false_predicate>::result));
    EXPECT_TRUE((none_of<iterator_begin<empty_list>, iterator_end<empty_list>, as_inner_1>::result));
}

TEST_F(TLAlgorithmTests, NoneOfEmptyListReturnsTrue) {
    EXPECT_TRUE((none_of<iterator_begin<empty_list>, iterator_end<empty_list>, true_predicate>::result));
    EXPECT_TRUE((none_of<iterator_begin<empty_list>, iterator_end<empty_list>, false_predicate>::result));
    EXPECT_TRUE((none_of<iterator_begin<empty_list>, iterator_end<empty_list>, as_inner_1>::result));
}

TEST_F(TLAlgorithmTests, NoneOfPredOnceTrueReturnsFalse) {
    EXPECT_FALSE((none_of<iterator_begin<list_1>, iterator_end<list_1>, true_predicate>::result));
    EXPECT_FALSE((none_of<iterator_begin<list_1_1_1>, iterator_end<list_1_1_1>, as_inner_1>::result));
    EXPECT_FALSE((none_of<iterator_begin<list_1_2>, iterator_next<iterator_begin<list_1_2>>, as_inner_1>::result));
}

TEST_F(TLAlgorithmTests, NoneOfPredAlwaysFalseReturnsTrue) {
    EXPECT_TRUE((none_of<iterator_begin<list_1_2_3>, iterator_end<list_1_2_3>, false_predicate>::result));
    EXPECT_TRUE((none_of<iterator_next<iterator_begin<list_1_2>>, iterator_end<list_1_2>, as_inner_1>::result));
}

TEST_F(TLAlgorithmTests, FindTypeHasNestedResultType) {
    EXPECT_TRUE((has_type_result_v<find_type<iterator_begin<empty_list>, iterator_end<empty_list>, Inner1>>));
    EXPECT_TRUE((has_type_result_v<find_type<iterator_begin<list_1_2>, iterator_end<list_1_2>, Inner2>>));
    EXPECT_TRUE((has_type_result_v<find_type<iterator_begin<list_1_2_3>, iterator_end<list_1_2_3>, Inner3>>));
}

TEST_F(TLAlgorithmTests, FindTypeTypeNotFoundReturnsEndIterator) {
    EXPECT_TRUE((test_case<
        find_type<iterator_begin<empty_list>,iterator_end<empty_list>,Inner1>,
        iterator_end<empty_list>>()));

    EXPECT_TRUE((test_case<
        find_type<iterator_begin<list_2_3>,iterator_end<list_2_3>, Inner1>,
        iterator_end<list_2_3>>()));

    EXPECT_TRUE((test_case<
        find_type<iterator_begin<list_1_2>, iterator_prev<iterator_end<list_1_2>>, Inner2>,
        iterator_prev<iterator_end<list_1_2>>>()));
}

TEST_F(TLAlgorithmTests, FindTypeFoundReturnsIterator) {
    EXPECT_TRUE((test_case<
        find_type<iterator_begin<list_1_2>,iterator_end<list_1_2>,Inner1>,
        iterator_begin<list_1_2>>()));

    EXPECT_TRUE((test_case<
        find_type<iterator_begin<list_3_2_3>,iterator_end<list_3_2_3>, Inner2>,
        iterator_next<iterator_begin<list_3_2_3>>>()));

    EXPECT_TRUE((test_case<
        find_type<iterator_begin<list_1_2>, iterator_prev<iterator_end<list_1_2>>, Inner1>,
        iterator_begin<list_1_2>>()));
}

TEST_F(TLAlgorithmTests, FindTypeIfHasNestedResultType) {
    EXPECT_TRUE((has_type_result_v<find_type_if<iterator_begin<empty_list>, iterator_end<empty_list>, true_predicate>>));
    EXPECT_TRUE((has_type_result_v<find_type_if<iterator_begin<list_1>, iterator_end<list_1>, false_predicate>>));
    EXPECT_TRUE((has_type_result_v<find_type_if<iterator_begin<list_1_2>, iterator_end<list_1_2>, as_inner_1>>));
}

TEST_F(TLAlgorithmTests, FindTypeIfPredTrueReturnsIterator) {
    EXPECT_TRUE((test_case<
        find_type_if<iterator_begin<list_1_2>,iterator_end<list_1_2>, as_inner_1>,
        iterator_begin<list_1_2>>()));

    EXPECT_TRUE((test_case<
        find_type_if<iterator_begin<list_3_2_3>,iterator_end<list_3_2_3>, as_inner_2>,
        iterator_next<iterator_begin<list_3_2_3>>>()));

    EXPECT_TRUE((test_case<
        find_type_if<iterator_begin<list_1_2>, iterator_prev<iterator_end<list_1_2>>, as_inner_1>,
        iterator_begin<list_1_2>>()));
}

TEST_F(TLAlgorithmTests, FindTypeIfPredAlwaysFalseReturnsEndIterator) {
    EXPECT_TRUE((test_case<
        find_type_if<iterator_begin<empty_list>,iterator_end<empty_list>, true_predicate>,
        iterator_end<empty_list>>()));

    EXPECT_TRUE((test_case<
        find_type_if<iterator_begin<empty_list>,iterator_end<empty_list>, false_predicate>,
        iterator_end<empty_list>>()));

    EXPECT_TRUE((test_case<
        find_type_if<iterator_begin<list_2_3>,iterator_end<list_2_3>, as_inner_1>,
        iterator_end<list_2_3>>()));

    EXPECT_TRUE((test_case<
        find_type_if<iterator_begin<list_1_2>, iterator_prev<iterator_end<list_1_2>>, as_inner_2>,
        iterator_prev<iterator_end<list_1_2>>>()));
}

TEST_F(TLAlgorithmTests, TypeCountHasNestedResultValue) {
    EXPECT_TRUE((has_value_result_v<
            type_count<iterator_begin<empty_list>, iterator_end<empty_list>, Inner1>>));
    EXPECT_TRUE((has_value_result_v<
            type_count<iterator_begin<list_1_2>, iterator_end<list_1_2>, Inner2>>));
    EXPECT_TRUE((has_value_result_v<
            type_count<iterator_begin<list_1_2>, iterator_prev<iterator_end<list_1_2>>, Inner3>>));
}

TEST_F(TLAlgorithmTests, TypeCountTypeNotFoundReturns0) {
    EXPECT_EQ(0, (type_count<iterator_begin<empty_list>, iterator_end<empty_list>, Inner1>::result));
    EXPECT_EQ(0, (type_count<iterator_begin<list_1_2>, iterator_end<list_1_2>, Inner3>::result));
    EXPECT_EQ(0, (type_count<iterator_begin<list_1_2_3>, iterator_prev<iterator_end<list_1_2_3>>, Inner3>::result));
}
TEST_F(TLAlgorithmTests, TypeCountReturnsTypeAmountInTheList) {
    EXPECT_EQ(3, (type_count<iterator_begin<list_1_1_1>, iterator_end<list_1_1_1>, Inner1>::result));
    EXPECT_EQ(2, (type_count<iterator_begin<list_3_2_3>, iterator_end<list_3_2_3>, Inner3>::result));
    EXPECT_EQ(1, (type_count<iterator_begin<list_3_2_3>, iterator_end<list_3_2_3>, Inner2>::result));
    EXPECT_EQ(1, (type_count<iterator_next<iterator_begin<list_1_2>>, iterator_end<list_1_2>, Inner2>::result));
    EXPECT_EQ(0, (type_count_if<iterator_begin<list_1_2>, iterator_prev<iterator_end<list_1_2>>, as_inner_2>::result));
}

TEST_F(TLAlgorithmTests, TypeCountIfHasNestedResultValue) {
    EXPECT_TRUE((has_value_result_v<
            type_count_if<iterator_begin<empty_list>, iterator_end<empty_list>, true_predicate>>));
    EXPECT_TRUE((has_value_result_v<
            type_count_if<iterator_begin<list_1_2>, iterator_end<list_1_2>, false_predicate>>));
    EXPECT_TRUE((has_value_result_v<
            type_count_if<iterator_begin<list_1_2>, iterator_prev<iterator_end<list_1_2>>, as_inner_3>>));
}

TEST_F(TLAlgorithmTests, TypeCountIfPredAlwaysFalseReturns0) {
    EXPECT_EQ(0, (type_count_if<iterator_begin<empty_list>, iterator_end<empty_list>, as_inner_1>::result));
    EXPECT_EQ(0, (type_count_if<iterator_begin<list_1_2>, iterator_end<list_1_2>, as_inner_3>::result));
    EXPECT_EQ(0, (type_count_if<iterator_begin<list_1_2_3>, iterator_prev<iterator_end<list_1_2_3>>, as_inner_3>::result));
}

TEST_F(TLAlgorithmTests, TypeCountIfReturnsTypeAmountInTheList) {
    EXPECT_EQ(3, (type_count_if<iterator_begin<list_1_1_1>, iterator_end<list_1_1_1>, as_inner_1>::result));
    EXPECT_EQ(2, (type_count_if<iterator_begin<list_3_2_3>, iterator_end<list_3_2_3>, as_inner_3>::result));
    EXPECT_EQ(1, (type_count_if<iterator_begin<list_3_2_3>, iterator_end<list_3_2_3>, as_inner_2>::result));
    EXPECT_EQ(1, (type_count_if<iterator_next<iterator_begin<list_1_2>>, iterator_end<list_1_2>, as_inner_2>::result));
    EXPECT_EQ(0, (type_count_if<iterator_begin<list_1_2>, iterator_prev<iterator_end<list_1_2>>, as_inner_2>::result));
}

TEST_F(TLAlgorithmTests, EqualHasNestedResultValue) {
    EXPECT_TRUE((has_value_result_v<
        equal<iterator_begin<empty_list>, iterator_end<empty_list>, iterator_begin<list_1>>>));
    EXPECT_TRUE((has_value_result_v<
        equal<iterator_begin<empty_list>, iterator_end<empty_list>, iterator_begin<list_1>, b_true_predicate>>));
    EXPECT_TRUE((has_value_result_v<
        equal<iterator_begin<empty_list>, iterator_end<empty_list>, iterator_begin<list_1>, b_false_predicate>>));
}

TEST_F(TLAlgorithmTests, TestEqual) {
    EXPECT_EQ(0, 1);
}

TEST_F(TLAlgorithmTests, TestSameTypes) {
    EXPECT_EQ(0, 1);
}

TEST_F(TLAlgorithmTests, TestSwap) {
    EXPECT_EQ(0, 1);
}

TEST_F(TLAlgorithmTests, TestSwapIter) {
    EXPECT_EQ(0, 1);
}

TEST_F(TLAlgorithmTests, TestSwapRanges) {
    EXPECT_EQ(0, 1);
}

} //testing
} //tl
