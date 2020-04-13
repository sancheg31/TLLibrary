#pragma once

#include "TLTestBase.hpp"
#include "TLTestCase.hpp"

#include "source/TLfwd.hpp"
#include "source/TLTraits.hpp"
#include "source/TLIterator.hpp"

namespace TL {
namespace testing {

class TLIteratorTests: TLTestBase {
public:
    TLIteratorTests(const std::string& name): TLTestBase(name) { }
    virtual void executeTrue() override {

    }

    virtual void executeFalse() override {

    }

private:

    void emptyList_list_returnEmptyList_success();
    void emptyList_type_failure();
    void emptyList_next_failure();
    void emptyList_prev_failure();

    void singletonList_list_success();
    void singletionList_type_return1_success();
    void singletonList_next_returnEnd_success();
    void singletonList_prevOnEnd_success();
    void singletonList_prev_failure();

    void integralList_type_returnN_success();
    void integralList_next_success();
    void integralList_prev_success();
    void integralList_list_success();
    void integralList_typeAtEnd_failure();
    void integralList_nextAtEnd_failure();
    void integralList_prevAtBegin_failure();

    void doublesList_type_returnN_success();
    void doublesList_next_success();
    void doublesList_prev_success();
    void doublesList_list_success();
    void doublesList_typeAtEnd_failure();
    void doublesList_nextAtEnd_failure();
    void doublesList_prevAtBegin_failure();

    template <std::size_t I>
    using e_iter = type_list_iterator<empty_list, I>;
    template <std::size_t I>
    using s_iter = type_list_iterator<singleton_list, I>;
    template <std::size_t I>
    using i_iter = type_list_iterator<integrals, I>;
    template <std::size_t I>
    using d_iter = type_list_iterator<doubles, I>;

    template <class T, class U>
    static constexpr bool is_same_v = traits::is_same<T, U>::value;

    template <typename Iter>
    using it_type = typename Iter::type;
    template <typename Iter>
    using it_list = typename Iter::list;
    template <typename Iter>
    using it_next = typename Iter::next;
    template <typename Iter>
    using it_prev = typename Iter::prev;

};

} //testing
} //tl
