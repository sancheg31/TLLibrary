
#include "TLIteratorTests.hpp"

namespace TL {
namespace testing {

void TLIteratorTests::emptyList_list_returnEmptyList_success() {
    static_assert(is_same_v<it_list<e_iter<0>>, empty_list>, "list is not equal empty_list");
}

void TLIteratorTests::emptyList_type_failure() {
    //(void)it_type<e_iter<0>>{};
    //(void)it_type<e_iter<empty_list_size>>{};
}

void TLIteratorTests::emptyList_next_failure() {
    //(void)it_next<e_iter<0>>{};
    //(void)it_next<e_iter<empty_list_size>>{};
}

void TLIteratorTests::emptyList_prev_failure() {
    //(void)it_prev<e_iter<0>>{};
    //(void)it_prev<e_iter<empty_list_size>>{};
}

void TLIteratorTests::singletonList_list_success() {
    static_assert(is_same_v<it_list<s_iter<0>>, singleton_list>, "list is not equal singleton_list");
}

void TLIteratorTests::singletionList_type_return1_success() {
    static_assert(is_same_v<it_type<s_iter<0>>, singleton_0>, "types are not equal");
}

void TLIteratorTests::singletonList_next_returnEnd_success() {
    static_assert(is_same_v<it_next<s_iter<0>>, s_iter<singleton_list_size>>, "types are not equal");
}

void TLIteratorTests::singletonList_prevOnEnd_success() {
    static_assert(is_same_v<it_prev<s_iter<singleton_list_size>>, s_iter<0>>, "types are not equal");
}

void TLIteratorTests::singletonList_prev_failure() {
    //(void)it_prev<s_iter<0>>{};
}

void TLIteratorTests::integralList_type_returnN_success() {
    static_assert(is_same_v<it_type<i_iter<0>>, integrals_0>, "type is incorrect");
    static_assert(is_same_v<it_type<i_iter<1>>, integrals_1>, "type is incorrect");
    static_assert(is_same_v<it_type<i_iter<2>>, integrals_2>, "type is incorrect");
    static_assert(is_same_v<it_type<i_iter<3>>, integrals_3>, "type is incorrect");
}

void TLIteratorTests::integralList_next_success() {
    static_assert(is_same_v<it_next<i_iter<0>>, i_iter<1>>, "next is incorrect");
    static_assert(is_same_v<it_next<i_iter<1>>, i_iter<2>>, "next is incorrect");
    static_assert(is_same_v<it_next<i_iter<integrals_size-1>>, i_iter<integrals_size>>, "next is incorrect");
}

void TLIteratorTests::integralList_prev_success() {
    static_assert(is_same_v<it_prev<i_iter<1>>, i_iter<0>>, "next is incorrect");
    static_assert(is_same_v<it_prev<i_iter<2>>, i_iter<1>>, "next is incorrect");
    static_assert(is_same_v<it_prev<i_iter<integrals_size>>, i_iter<integrals_size-1>>, "next is incorrect");
}

void TLIteratorTests::integralList_list_success() {
    static_assert(is_same_v<it_list<i_iter<0>>, integrals>, "list is not equal to integrals");
    static_assert(is_same_v<it_list<i_iter<1>>, integrals>, "list is not equal to integrals");
    static_assert(is_same_v<it_list<i_iter<integrals_size>>, integrals>, "list is not equal to integrals");
}

void TLIteratorTests::integralList_typeAtEnd_failure() {
    //(void)it_type<i_iter<integrals_size>>{};
}

void TLIteratorTests::integralList_nextAtEnd_failure() {
    //(void)it_next<i_iter<integrals_size>>{};
}

void TLIteratorTests::integralList_prevAtBegin_failure() {
    //(void)it_prev<i_iter<0>>{};
}

void TLIteratorTests::doublesList_type_returnN_success() {
    static_assert(is_same_v<it_type<d_iter<0>>, doubles_0>, "type is incorrect");
    static_assert(is_same_v<it_type<d_iter<1>>, doubles_1>, "type is incorrect");
    static_assert(is_same_v<it_next<d_iter<doubles_size-1>>, d_iter<doubles_size>>, "next is incorrect");
}

void TLIteratorTests::doublesList_next_success() {
    static_assert(is_same_v<it_next<d_iter<0>>, d_iter<1>>, "next is incorrect");
    static_assert(is_same_v<it_next<d_iter<1>>, d_iter<2>>, "next is incorrect");
}

void TLIteratorTests::doublesList_prev_success() {
    static_assert(is_same_v<it_prev<d_iter<1>>, d_iter<0>>, "next is incorrect");
    static_assert(is_same_v<it_prev<d_iter<2>>, d_iter<1>>, "next is incorrect");
    static_assert(is_same_v<it_prev<d_iter<doubles_size>>, d_iter<doubles_size-1>>, "next is incorrect");
}

void TLIteratorTests::doublesList_list_success() {
    static_assert(is_same_v<it_list<d_iter<0>>, doubles>, "type is incorrect");
    static_assert(is_same_v<it_list<d_iter<1>>, doubles>, "type is incorrect");
    static_assert(is_same_v<it_list<d_iter<doubles_size>>, doubles>, "type is incorrect");
}

void TLIteratorTests::doublesList_typeAtEnd_failure() {
    //(void)it_type<d_iter<doubles_size>>{};
    //(void)it_type<d_iter<doubles_size+1>>{};
}

void TLIteratorTests::doublesList_nextAtEnd_failure() {
    //(void)it_next<d_iter<doubles_size>>{};
}

void TLIteratorTests::doublesList_prevAtBegin_failure() {
    //(void)it_prev<d_iter<0>>{};
}

} //testing
} //tl
