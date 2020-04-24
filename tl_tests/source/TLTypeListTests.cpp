

#include "TLTypeListTests.hpp"

#include "source/TLMetaFunctionGenerators.hpp"
#include "source/type_list.hpp"
#include "source/TLTypeIterator.hpp"
#include "TLTestCase.hpp"

namespace TL {
namespace testing {


TEST_F(TLTypeListTests, TestLengthOperation) {
    EXPECT_EQ(length<empty_list>::value, empty_list_size);
    EXPECT_EQ(length<singleton_list>::value, singleton_list_size);
    EXPECT_EQ(length<integrals>::value, integrals_size);
    EXPECT_EQ(length<doubles>::value, doubles_size);
}

TEST_F(TLTypeListTests, TestEmptyOperation) {
    EXPECT_EQ(empty<empty_list>::value, true);
    EXPECT_EQ(empty<singleton_list>::value, false);
    EXPECT_EQ(empty<integrals>::value, false);
    EXPECT_EQ(empty<doubles>::value, false);
}

TEST_F(TLTypeListTests, TestHasTypeOperation) {
    struct Inner {};
    EXPECT_EQ((has_type<empty_list, Inner>::value), false);
    EXPECT_EQ((has_type<singleton_list, singleton_0>::value), true);
    EXPECT_EQ((has_type<singleton_list, Inner>::value), false);
    EXPECT_EQ((has_type<doubles, doubles_0>::value), true);
    EXPECT_EQ((has_type<doubles, doubles_1>::value), true);
    EXPECT_EQ((has_type<doubles, Inner>::value), false);
    EXPECT_EQ((has_type<integrals, integrals_0>::value), true);
    EXPECT_EQ((has_type<integrals, Inner>::value), false);
}

TEST_F(TLTypeListTests, TestGetTypeOperation) {
    EXPECT_TRUE((test_case<get_type<singleton_list, 0>, singleton_0>));
    EXPECT_TRUE((test_case<get_type<integrals, 0>, integrals_0>));
    EXPECT_TRUE((test_case<get_type<integrals, 1>, integrals_1>));
    EXPECT_TRUE((test_case<get_type<integrals, 2>, integrals_2>));
    EXPECT_TRUE((test_case<get_type<integrals, 3>, integrals_3>));
    EXPECT_TRUE((test_case<get_type<doubles, 0>, doubles_0>));
    EXPECT_TRUE((test_case<get_type<doubles, 1>, doubles_1>));
}

TEST_F(TLTypeListTests, TestFirstTypeOperation) {
    EXPECT_TRUE((test_case<first_type<singleton_list>, singleton_0>));
    EXPECT_TRUE((test_case<first_type<doubles>, doubles_0>));
    EXPECT_TRUE((test_case<first_type<integrals>, integrals_0>));
}

TEST_F(TLTypeListTests, TestLastTypeOperation) {
    EXPECT_TRUE((test_case<last_type<singleton_list>, singleton_0>));
    EXPECT_TRUE((test_case<last_type<doubles>, doubles_1>));
    EXPECT_TRUE((test_case<last_type<integrals>, integrals_3>));
}

TEST_F(TLTypeListTests, TestSetTypeOperation) {
    EXPECT_TRUE((test_case<set_type<list_1, Inner2, 0>, list_2>));
    EXPECT_TRUE((test_case<set_type<list_2, Inner3, 0>, list_3>));
    EXPECT_TRUE((test_case<set_type<list_1_2, Inner1, 1>, list_1_1>));
    EXPECT_TRUE((test_case<set_type<list_1, integrals, 0>, type_list<integrals>>));
    EXPECT_TRUE((test_case<set_type<list_1, empty_list, 0>, type_list<empty_list>>));
    EXPECT_TRUE((test_case<set_type<list_3_2_3, Inner1, 0>, list_1_2_3>));
    EXPECT_TRUE((test_case<set_type<list_1_2_3, Inner3, 0>, list_3_2_3>));
}

TEST_F(TLTypeListTests, TestTypeIndexOperation) {
    EXPECT_EQ((type_index<empty_list, Inner1>::value), -1);
    EXPECT_EQ((type_index<list_1_2_3, Inner1>::value), 0);
    EXPECT_EQ((type_index<list_1_2_3, Inner2>::value), 1);
    EXPECT_EQ((type_index<list_1_2_3, Inner3>::value), 2);
    EXPECT_EQ((type_index<list_1_2, Inner3>::value), -1);
}

TEST_F(TLTypeListTests, TestLastTypeIndexOperation) {
    EXPECT_EQ((last_type_index<empty_list, Inner1>::value), -1);
    EXPECT_EQ((last_type_index<list_1_2_3, Inner1>::value), 0);
    EXPECT_EQ((last_type_index<list_1_2_3, Inner2>::value), 1);
    EXPECT_EQ((last_type_index<list_1_2_3, Inner3>::value), 2);
    EXPECT_EQ((last_type_index<list_1_2, Inner3>::value), -1);
    EXPECT_EQ((last_type_index<list_1_1_1, Inner1>::value), 2);
    EXPECT_EQ((last_type_index<list_2_1_2, Inner2>::value), 2);
    EXPECT_EQ((last_type_index<list_3_2_3, Inner3>::value), 2);
}

TEST_F(TLTypeListTests, TestSwapOperation) {
    EXPECT_TRUE((test_case<swap<list_1_2_3, 0, 2>, list_3_2_1>()));
    EXPECT_TRUE((test_case<swap<list_1_2, 0, 1>, list_2_1>()));
    EXPECT_TRUE((test_case<swap<list_3_2_3, 1, 2>, list_3_3_2>()));
    EXPECT_TRUE((test_case<swap<list_1_1, 0, 1>, list_1_1>()));
    EXPECT_TRUE((test_case<swap<list_1, 0, 0>, list_1>()));
}

TEST_F(TLTypeListTests, TestAppendOperation) {
    EXPECT_TRUE((test_case<append<list_1_2, Inner3>, list_1_2_3>));
    EXPECT_TRUE((test_case<append<list_2_1, Inner2>, list_2_1_2>));
    EXPECT_TRUE((test_case<append<list_1, list_2>, list_1_2>));

    EXPECT_TRUE((test_case<append<empty_list, list_2_1>, list_2_1>));
    EXPECT_TRUE((test_case<append<empty_list, list_1_2_3>, list_1_2_3>));
    EXPECT_TRUE((test_case<append<list_1, empty_list>, list_1>));
    EXPECT_TRUE((test_case<append<list_1_2, empty_list>, list_1_2>));
    EXPECT_TRUE((test_case<append<empty_list, empty_list>, empty_list>));
}

TEST_F(TLTypeListTests, TestPrependOperation) {
    EXPECT_TRUE((test_case<prepend<list_2, Inner1>, list_1_2>));
    EXPECT_TRUE((test_case<prepend<list_2, list_1>, list_1_2>));
    EXPECT_TRUE((test_case<prepend<list_1, list_2>, list_2_1>));
    EXPECT_TRUE((test_case<prepend<list_2_3, Inner1>, list_1_2_3>));

    EXPECT_TRUE((test_case<prepend<empty_list, list_2_1>, list_2_1>));
    EXPECT_TRUE((test_case<prepend<empty_list, list_1_2_3>, list_1_2_3>));
    EXPECT_TRUE((test_case<prepend<list_1, empty_list>, list_1>));
    EXPECT_TRUE((test_case<prepend<list_1_2, empty_list>, list_1_2>));
    EXPECT_TRUE((test_case<prepend<empty_list, empty_list>, empty_list>));
}

TEST_F(TLTypeListTests, TestPushBackOperation) {
    EXPECT_TRUE((test_case<push_back<list_1_2, Inner3>, list_1_2_3>));
    EXPECT_TRUE((test_case<push_back<list_2_1, Inner2>, list_2_1_2>));

    EXPECT_TRUE((test_case<push_back<empty_list, Inner1>, list_1>));
    EXPECT_TRUE((test_case<push_back<empty_list, Inner2>, list_2>));
}

TEST_F(TLTypeListTests, TestPushFrontOperation) {
    EXPECT_TRUE((test_case<push_front<list_2, Inner1>, list_1_2>));
    EXPECT_TRUE((test_case<push_front<list_2_3, Inner1>, list_1_2_3>));

    EXPECT_TRUE((test_case<push_front<empty_list, Inner1>, list_1>));
    EXPECT_TRUE((test_case<push_front<empty_list, Inner2>, list_2>));
}

TEST_F(TLTypeListTests, TestPopBackOperation) {
    EXPECT_TRUE((test_case<pop_back<list_1_2_3>, list_1_2>));
    EXPECT_TRUE((test_case<pop_back<list_1_2>, list_1>));
    EXPECT_TRUE((test_case<pop_back<list_1>, empty_list>));
    EXPECT_TRUE((test_case<pop_back<list_2_1_2>, list_2_1>));
}

TEST_F(TLTypeListTests, TestPopFrontOperation) {
    EXPECT_TRUE((test_case<pop_front<list_1_2_3>, list_2_3>));
    EXPECT_TRUE((test_case<pop_front<list_1_2>, list_2>));
    EXPECT_TRUE((test_case<pop_front<list_1>, empty_list>));
    EXPECT_TRUE((test_case<pop_front<list_2_1_2>, list_1_2>));
}

TEST_F(TLTypeListTests, TestEraseOperation) {
    EXPECT_TRUE((test_case<erase<type_iterator<list_1_2, 1>, type_iterator<list_1_2, 2>>, list_1>()));
    EXPECT_TRUE((test_case<erase<type_iterator<list_1_2_3, 0>, type_iterator<list_1_2_3, 3>>, empty_list>()));
    EXPECT_TRUE((test_case<erase<type_iterator<list_1_2_1, 0>, type_iterator<list_1_2_1, 2>>, list_1>()));
    EXPECT_TRUE((test_case<erase<type_iterator<list_1_2_3, 0>, type_iterator<list_1_2_3, 1>>, list_2_3>()));
    EXPECT_TRUE((test_case<erase<type_iterator<list_1_2_1, 0>, type_iterator<list_1_2_1, 0>>, list_1_2_1>()));
    EXPECT_TRUE((test_case<erase<type_iterator<list_1_2, 2>, type_iterator<list_1_2, 2>>, list_1_2>()));
    EXPECT_TRUE((test_case<erase<type_iterator<empty_list, 0>, type_iterator<empty_list, 0>>, empty_list>()));
}




} //testing
} // TL

