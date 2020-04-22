
#include "TLTypeIteratorTests.hpp"

#include <gtest/gtest.h>

namespace TL {
namespace testing {



TEST_F(TLTypeIteratorTests, TestListPropertyPresence) {
    EXPECT_EQ(true, (has_type_list_v< iterator_properties<empty_iter<0>> >));
    EXPECT_EQ(true, (has_type_list_v< iterator_properties<empty_iter<empty_list_size>> >));
    EXPECT_EQ(true, (has_type_list_v< iterator_properties<single_iter<0>> >));
    EXPECT_EQ(true, (has_type_list_v< iterator_properties<single_iter<singleton_list_size>> >));
    EXPECT_EQ(true, (has_type_list_v< iterator_properties<int_iter<0>> >));
    EXPECT_EQ(true, (has_type_list_v< iterator_properties<int_iter<integrals_size>> >));
    EXPECT_EQ(true, (has_type_list_v< iterator_properties<double_iter<1>> >));
    EXPECT_EQ(true, (has_type_list_v< iterator_properties<double_iter<doubles_size>> >));
}

TEST_F(TLTypeIteratorTests, TestListPropertyContent) {
    EXPECT_EQ(true, (is_same_v<iterator_list<empty_iter<0>>, empty_list>));
    EXPECT_EQ(true, (is_same_v<iterator_list<single_iter<0>>, singleton_list>));
    EXPECT_EQ(true, (is_same_v<iterator_list<int_iter<0>>, integrals>));
    EXPECT_EQ(true, (is_same_v<iterator_list<double_iter<0>>, doubles>));
    EXPECT_EQ(true, (is_same_v<iterator_list<empty_iter<empty_list_size>>, empty_list>));
    EXPECT_EQ(true, (is_same_v<iterator_list<single_iter<singleton_list_size>>, singleton_list>));
    EXPECT_EQ(true, (is_same_v<iterator_list<int_iter<integrals_size>>, integrals>));
    EXPECT_EQ(true, (is_same_v<iterator_list<double_iter<doubles_size>>, doubles>));
}

TEST_F(TLTypeIteratorTests, TestValuePropertyPresence) {
    EXPECT_EQ(false, (has_type_value_v<empty_iter<0>>));
    EXPECT_EQ(false, (has_type_value_v<empty_iter<empty_list_size>>));
    EXPECT_EQ(true, (has_type_value_v<single_iter<0>>));
    EXPECT_EQ(false, (has_type_value_v<single_iter<singleton_list_size>>));
    EXPECT_EQ(true, (has_type_value_v<int_iter<0>>));
    EXPECT_EQ(false, (has_type_value_v<int_iter<integrals_size>>));
    EXPECT_EQ(true, (has_type_value_v<double_iter<1>>));
    EXPECT_EQ(false, (has_type_value_v<double_iter<doubles_size>>));
}

TEST_F(TLTypeIteratorTests, TestValuePropertyContent) {
    EXPECT_EQ(true, (is_same_v<iterator_value<single_iter<0>>, singleton_0>));
    EXPECT_EQ(true, (is_same_v<iterator_value<int_iter<0>>, integrals_0>));
    EXPECT_EQ(true, (is_same_v<iterator_value<int_iter<1>>, integrals_1>));
    EXPECT_EQ(true, (is_same_v<iterator_value<int_iter<2>>, integrals_2>));
    EXPECT_EQ(true, (is_same_v<iterator_value<int_iter<3>>, integrals_3>));
    EXPECT_EQ(true, (is_same_v<iterator_value<double_iter<0>>, doubles_0>));
    EXPECT_EQ(true, (is_same_v<iterator_value<double_iter<1>>, doubles_1>));
}

TEST_F(TLTypeIteratorTests, TestSetValuePropertyPresence) {
    EXPECT_EQ(false, (has_type_set_value_v<empty_iter<0>>));
    EXPECT_EQ(false, (has_type_set_value_v<empty_iter<empty_list_size>>));
    EXPECT_EQ(true, (has_type_set_value_v<single_iter<0>>));
    EXPECT_EQ(false, (has_type_set_value_v<single_iter<singleton_list_size>>));
    EXPECT_EQ(true, (has_type_set_value_v<int_iter<0>>));
    EXPECT_EQ(false, (has_type_set_value_v<int_iter<integrals_size>>));
    EXPECT_EQ(true, (has_type_set_value_v<double_iter<0>>));
    EXPECT_EQ(true, (has_type_set_value_v<double_iter<1>>));
    EXPECT_EQ(false, (has_type_set_value_v<double_iter<doubles_size>>));
}

TEST_F(TLTypeIteratorTests, TestSetValuePropertyContent) {
    struct Inner { };
    using new_it = iterator_set_value<single_iter<0>, Inner>;
    EXPECT_EQ(true, (is_same_v<iterator_value<new_it>, Inner>));
    EXPECT_EQ(true, (is_same_v<iterator_value<iterator_set_value<int_iter<0>, Inner>>, Inner>));
    EXPECT_EQ(true, (is_same_v<iterator_value<iterator_set_value<int_iter<integrals_size-1>, Inner>>, Inner>));
    EXPECT_EQ(true, (is_same_v<iterator_value<iterator_set_value<double_iter<doubles_size-1>, empty_list>>, empty_list>));
    EXPECT_EQ(true, (is_same_v<iterator_value<iterator_set_value<single_iter<0>, empty_list>>, empty_list>));
}

TEST_F(TLTypeIteratorTests, TestNextPropertyPresence) {
    EXPECT_EQ(false, (has_type_next_v<empty_iter<0>>));
    EXPECT_EQ(false, (has_type_next_v<empty_iter<empty_list_size>>));
    EXPECT_EQ(true, (has_type_next_v<single_iter<0>>));
    EXPECT_EQ(false, (has_type_next_v<single_iter<singleton_list_size>>));
    EXPECT_EQ(true, (has_type_next_v<int_iter<0>>));
    EXPECT_EQ(true, (has_type_next_v<int_iter<integrals_size - 1>>));
    EXPECT_EQ(false, (has_type_next_v<int_iter<integrals_size>>));
    EXPECT_EQ(true, (has_type_next_v<double_iter<0>>));
    EXPECT_EQ(false, (has_type_next_v<double_iter<doubles_size>>));
}

TEST_F(TLTypeIteratorTests, TestNextPropertyContent) {
    EXPECT_EQ(true, (is_same_v<iterator_next<single_iter<0>>, single_iter<1>>));
    EXPECT_EQ(true, (is_same_v<iterator_next<single_iter<0>>, single_iter<singleton_list_size>>));
    EXPECT_EQ(true, (is_same_v<iterator_next<int_iter<0>>, int_iter<1>>));
    EXPECT_EQ(true, (is_same_v<iterator_next<int_iter<1>>, int_iter<2>>));
    EXPECT_EQ(true, (is_same_v<iterator_next<int_iter<2>>, int_iter<3>>));
    EXPECT_EQ(true, (is_same_v<iterator_next<int_iter<3>>, int_iter<4>>));
    EXPECT_EQ(true, (is_same_v<iterator_next<int_iter<3>>, int_iter<integrals_size>>));
    EXPECT_EQ(true, (is_same_v<iterator_next<double_iter<0>>, double_iter<1>>));
    EXPECT_EQ(true, (is_same_v<iterator_next<double_iter<1>>, double_iter<2>>));
    EXPECT_EQ(true, (is_same_v<iterator_next<double_iter<1>>, double_iter<doubles_size>>));
}

TEST_F(TLTypeIteratorTests, TestPrevPropertyPresence) {
    EXPECT_EQ(false, (has_type_prev_v<empty_iter<0>>));
    EXPECT_EQ(false, (has_type_prev_v<empty_iter<empty_list_size>>));
    EXPECT_EQ(false, (has_type_prev_v<single_iter<0>>));
    EXPECT_EQ(true, (has_type_prev_v<single_iter<singleton_list_size>>));
    EXPECT_EQ(false, (has_type_prev_v<int_iter<0>>));
    EXPECT_EQ(true, (has_type_prev_v<int_iter<integrals_size - 1>>));
    EXPECT_EQ(true, (has_type_prev_v<int_iter<integrals_size>>));
    EXPECT_EQ(false, (has_type_prev_v<double_iter<0>>));
    EXPECT_EQ(true, (has_type_prev_v<double_iter<doubles_size>>));
}

TEST_F(TLTypeIteratorTests, TestPrevPropertyContent) {
    EXPECT_EQ(true, (is_same_v<iterator_prev<single_iter<1>>, single_iter<0>>));
    EXPECT_EQ(true, (is_same_v<iterator_prev<single_iter<singleton_list_size>>, single_iter<0>>));
    EXPECT_EQ(true, (is_same_v<iterator_prev<int_iter<1>>, int_iter<0>>));
    EXPECT_EQ(true, (is_same_v<iterator_prev<int_iter<2>>, int_iter<1>>));
    EXPECT_EQ(true, (is_same_v<iterator_prev<int_iter<3>>, int_iter<2>>));
    EXPECT_EQ(true, (is_same_v<iterator_prev<int_iter<4>>, int_iter<3>>));
    EXPECT_EQ(true, (is_same_v<iterator_prev<int_iter<integrals_size>>, int_iter<3>>));
    EXPECT_EQ(true, (is_same_v<iterator_prev<double_iter<1>>, double_iter<0>>));
    EXPECT_EQ(true, (is_same_v<iterator_prev<double_iter<2>>, double_iter<1>>));
    EXPECT_EQ(true, (is_same_v<iterator_prev<double_iter<doubles_size>>, double_iter<1>>));
}

TEST_F(TLTypeIteratorTests, TestPositionPropertyPresence) {
    EXPECT_EQ(0, 1);
}

TEST_F(TLTypeIteratorTests, TestPositionPropertyContent) {
    EXPECT_EQ(0, 1);
}

TEST_F(TLTypeIteratorTests, TestAdvancePropertyPresence) {
    EXPECT_EQ(0, 1);
}

TEST_F(TLTypeIteratorTests, TestAdvancePropertyContent) {
    EXPECT_EQ(0, 1);
}

TEST_F(TLTypeIteratorTests, TestDistancePropertyPresence) {
    EXPECT_EQ(0, 1);
}

TEST_F(TLTypeIteratorTests, TestDistancePropertyContent) {
    EXPECT_EQ(0, 1);
}



} //testing
} //tl
