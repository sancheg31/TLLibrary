
#include "TLAlgorithmTests.hpp"
#include "TLTestCase.hpp"

#include "source/TLAlgorithm.hpp"
#include "source/TLTypeIterator.hpp"
#include "source/type_list.hpp"



namespace TL {
namespace testing {


TEST_F(TLAlgorithmTests, AllOfHasNestedValueResult) {
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



TEST_F(TLAlgorithmTests, AnyOfHasNestedValueResult) {
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



TEST_F(TLAlgorithmTests, NoneOfHasNestedValueResult) {
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



TEST_F(TLAlgorithmTests, FindTypeHasNestedTypeResult) {
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



TEST_F(TLAlgorithmTests, FindTypeIfHasNestedTypeResult) {
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



TEST_F(TLAlgorithmTests, TypeCountHasNestedValueResult) {
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



TEST_F(TLAlgorithmTests, TypeCountIfHasNestedValueResult) {
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



TEST_F(TLAlgorithmTests, EqualHasNestedValueResult) {
    EXPECT_TRUE((has_value_result_v<
        equal<iterator_begin<empty_list>, iterator_end<empty_list>, iterator_begin<list_1>>>));
    EXPECT_TRUE((has_value_result_v<
        equal<iterator_begin<empty_list>, iterator_end<empty_list>, iterator_begin<list_1>, b_true_predicate>>));
    EXPECT_TRUE((has_value_result_v<
        equal<iterator_begin<empty_list>, iterator_end<empty_list>, iterator_begin<list_1>, b_false_predicate>>));
}

TEST_F(TLAlgorithmTests, EqualEmptyRangeAlwaysReturnsTrue) {
    EXPECT_TRUE((test_case<
        equal<iterator_begin<empty_list>,
            iterator_end<empty_list>,
            iterator_begin<empty_list>,
            b_false_predicate>, true>()));
    EXPECT_TRUE((test_case<
        equal<iterator_begin<empty_list>,
                iterator_end<empty_list>,
                iterator_begin<list_1_2>,
                b_true_predicate>, true>()));
    EXPECT_TRUE((test_case<
        equal<iterator_begin<list_1_2>,
            iterator_begin<list_1_2>,
            iterator_end<list_1_2>>, true>()));
    EXPECT_TRUE((test_case<
        equal<iterator_end<list_1_2_3>,
            iterator_end<list_1_2_3>,
            iterator_begin<list_1_2>,
            b_false_predicate>, true>()));

}

TEST_F(TLAlgorithmTests, EqualRangesAreEqualReturnsTrue) {
    EXPECT_TRUE((test_case<
        equal<iterator_begin<empty_list>, iterator_end<empty_list>, iterator_begin<empty_list>>, true>()));
    EXPECT_TRUE((test_case<
        equal<iterator_begin<list_2_3>, iterator_end<list_2_3>, iterator_next<iterator_begin<list_1_2_3>>>, true>()));
    EXPECT_TRUE((test_case<
        equal<iterator_begin<list_1_2_3>, iterator_prev<iterator_end<list_1_2_3>>, iterator_begin<list_1_2>>, true>()));
    EXPECT_TRUE((test_case<
        equal<iterator_begin<list_1_2_3>, iterator_end<list_1_2_3>, iterator_begin<list_1_1_1>, b_true_predicate>, true>()));
}

TEST_F(TLAlgorithmTests, EqualRangesAreNotEqualReturnsFalse) {
    EXPECT_FALSE((equal<
        iterator_begin<list_1_2>, iterator_end<list_1_2>, iterator_begin<list_3_2_3>>::result));
    EXPECT_FALSE((equal<
        iterator_begin<list_1>, iterator_end<list_1>, iterator_begin<list_2>>::result));
    EXPECT_FALSE((equal<
        iterator_begin<list_1_2>, iterator_end<list_1_2>, iterator_begin<list_1_2>, b_false_predicate>::result));
    EXPECT_FALSE((equal<
        iterator_begin<list_1_2_3>, iterator_end<list_1_2_3>, iterator_begin<list_3_2_3>>::result));
}

TEST_F(TLAlgorithmTests, SameTypesHasNestedValueResult) {
    EXPECT_TRUE((has_value_result_v <
        same_types<iterator_begin<empty_list>, iterator_end<empty_list>, iterator_begin<empty_list>>
                                    >));
    EXPECT_TRUE((has_value_result_v <
        same_types<iterator_begin<list_1_2>, iterator_end<list_1_2>, iterator_begin<list_1_2>, b_true_predicate>
                                    >));
    EXPECT_TRUE((has_value_result_v <
        same_types<iterator_begin<list_1>, iterator_end<list_1>, iterator_begin<list_1>, b_false_predicate>
                                    >));
}

TEST_F(TLAlgorithmTests, SameTypesEmptyRangeAlwaysReturnsTrue) {

    EXPECT_TRUE((test_case<
        same_types<iterator_begin<empty_list>,
            iterator_end<empty_list>,
            iterator_begin<empty_list>,
            b_false_predicate>, true>()));

    EXPECT_TRUE((test_case<
        same_types<iterator_begin<empty_list>,
                iterator_end<empty_list>,
                iterator_begin<list_1_2>,
                b_true_predicate>, true>()));

    EXPECT_TRUE((test_case<
        same_types<iterator_begin<list_1_2>,
            iterator_begin<list_1_2>,
            iterator_end<list_1_2>>, true>()));

    EXPECT_TRUE((test_case<
        same_types<iterator_end<list_1_2_3>,
            iterator_end<list_1_2_3>,
            iterator_begin<list_1_2>,
            b_false_predicate>, true>()));
}

TEST_F(TLAlgorithmTests, SameTypesRangesHasSameTypesReturnsTrue) {

    EXPECT_TRUE((same_types<iterator_begin<list_1_2>,
                            iterator_end<list_1_2>,
                            iterator_begin<list_2_1>>::result));

    EXPECT_TRUE((same_types<iterator_next<iterator_begin<list_1_2_3>>,
                            iterator_end<list_1_2_3>,
                            iterator_begin<list_2_3>>::result));

    EXPECT_TRUE((same_types<iterator_begin<list_1_2_3>,
                            iterator_end<list_1_2_3>,
                            iterator_begin<list_3_2_3>,
                            b_true_predicate>::result));

    EXPECT_TRUE((same_types<iterator_begin<list_1_2>,
                             iterator_end<list_1_2>,
                             iterator_begin<list_2_1>,
                    b_false_predicate>::result));

    EXPECT_TRUE((same_types<iterator_begin<list_3_2_3>,
                            iterator_prev<iterator_end<list_3_2_3>>,
                            iterator_begin<list_2_3>>::result));
}

TEST_F(TLAlgorithmTests, SameTypesRangesHasDistinctTypesReturnsFalse) {

    EXPECT_FALSE((same_types<iterator_begin<list_1_2>,
                             iterator_end<list_1_2>,
                             iterator_begin<list_3_2>>::result));

    EXPECT_FALSE((same_types<iterator_begin<list_3_2_3>,
                             iterator_end<list_3_2_3>,
                             iterator_begin<list_1_2_3>>::result));

    EXPECT_FALSE((same_types<iterator_begin<list_1_2_3>,
                             iterator_prev<iterator_end<list_1_2_3>>,
                             iterator_begin<list_2_3>>::result));
}

TEST_F(TLAlgorithmTests, SwapIterHasNestedTypeResult) {
    EXPECT_TRUE((has_type_result_v< swap_iter<  iterator_begin<list_1>,
                                                iterator_prev<iterator_end<list_1>> > >));

    EXPECT_TRUE((has_type_result_v< swap_iter<  iterator_begin<list_2_3>,
                                                iterator_prev<iterator_end<list_2_3>> > >));

    EXPECT_TRUE((has_type_result_v< swap_iter<  iterator_next<iterator_begin<list_1_2_3>>,
                                                iterator_prev<iterator_end<list_1_2_3>> > >));

}

TEST_F(TLAlgorithmTests, SwapIterNewListHasSwappedElements) {
    using it_pair = typename swap_iter<iterator_begin<list_1_2>, iterator_next<iterator_begin<list_1_2>> >::result;
    using first = typename get_type<it_pair, 0>::type;
    using second = typename get_type<it_pair, 1>::type;

    EXPECT_TRUE((is_same_v<iterator_list<first>, list_2_2>));
    EXPECT_TRUE((is_same_v<iterator_list<second>, list_1_1>));
    EXPECT_TRUE((is_same_v<iterator_value<first>, Inner2>));
    EXPECT_TRUE((is_same_v<iterator_value<second>, Inner1>));

    using it_pair_2 = typename swap_iter<iterator_begin<list_1_2_3>, iterator_next<iterator_begin<list_1_2_3>> >::result;
    using first_2 = typename get_type<it_pair_2, 0>::type;
    using second_2 = typename get_type<it_pair_2, 1>::type;

    EXPECT_TRUE((is_same_v<iterator_list<first_2>, list_2_2_3>));
    EXPECT_TRUE((is_same_v<iterator_list<second_2>, list_1_1_3>));
    EXPECT_TRUE((is_same_v<iterator_value<first_2>, Inner2>));
    EXPECT_TRUE((is_same_v<iterator_value<second_2>, Inner1>));
}

TEST_F(TLAlgorithmTests, SwapRangesHasNestedTypeResult) {
    EXPECT_TRUE((has_type_result_v<swap_ranges<
                                        iterator_begin<empty_list>,
                                        iterator_begin<empty_list>,
                                        iterator_begin<empty_list>>>));
    EXPECT_TRUE((has_type_result_v<swap_ranges<
                                        iterator_begin<list_1>,
                                        iterator_end<list_1>,
                                        iterator_begin<list_1_2_3>>>));
}


TEST_F(TLAlgorithmTests, SwapRangesReturnsEndIteratorsWithSwappedRanges) {

    using new_iters = typename swap_ranges<iterator_begin<list_1_3>,
                                            iterator_end<list_1_3>,
                                            iterator_begin<list_3_2_1>>::result;

    using first = typename get_type<new_iters, 0>::type;
    using second = typename get_type<new_iters, 1>::type;

    EXPECT_TRUE((is_same_v<iterator_list<first>, list_3_2>));
    EXPECT_TRUE((is_same_v<iterator_list<second>, list_1_3_1>));
    EXPECT_TRUE((is_same_v<iterator_end<iterator_list<first>>, first>));
    EXPECT_TRUE((is_same_v<iterator_value<second>, Inner1>));
    EXPECT_TRUE((is_same_v<iterator_prev<iterator_end<iterator_list<second>>>, second>));

    using new_iters_2 = typename swap_ranges<iterator_begin<list_1>,
                                                iterator_end<list_1>,
                                                iterator_begin<list_2_1_2>>::result;
    using first_2 = typename get_type<new_iters_2, 0>::type;
    using second_2 = typename get_type<new_iters_2, 1>::type;

    EXPECT_TRUE((is_same_v<iterator_list<first_2>, list_2>));
    EXPECT_TRUE((is_same_v<iterator_list<second_2>, list_1_1_2>));
    EXPECT_TRUE((is_same_v<iterator_value<second_2>, Inner1>));
    EXPECT_TRUE((is_same_v<iterator_end<iterator_list<first_2>>, first_2>));
    EXPECT_TRUE((is_same_v<iterator_next<iterator_begin<iterator_list<second_2>>>, second_2>));
}

TEST_F(TLAlgorithmTests, SwapRangesEmptyRangesDoesNothing) {

    using it_1 = iterator_begin<list_1>;
    using it_2 = iterator_begin<list_1>;
    using it_3 = iterator_begin<list_3_2_3>;

    using new_iters = typename swap_ranges<it_1, it_2, it_3>::result;
    using first = typename get_type<new_iters, 0>::type;
    using second = typename get_type<new_iters, 1>::type;

    EXPECT_TRUE((is_same_v<it_1, first>));
    EXPECT_TRUE((is_same_v<it_2, first>));
    EXPECT_TRUE((is_same_v<it_3, second>));
    EXPECT_TRUE((is_same_v<iterator_list<first>, list_1>));
    EXPECT_TRUE((is_same_v<iterator_list<second>, list_3_2_3>));

}



TEST_F(TLAlgorithmTests, EraseHasNestedTypeResult) {
    EXPECT_EQ(1, 0);
}


} //testing
} //tl
