#pragma once

#include <gtest/gtest.h>

#include "source/TLMetaFunctionGenerators.hpp"
#include "TLTestBase.hpp"

namespace TL {
namespace testing {

class TLAlgorithmTests: public ::testing::Test, public TLTestBase
{
protected:
    TL_HAS_NESTED_TYPE(result)
    TL_HAS_NESTED_VALUE(result)

    template <typename T>
    struct true_predicate {
        enum { value = true };
    };

    template <typename T>
    struct false_predicate {
        enum { value = false };
    };

    template <typename T, typename U>
    struct b_true_predicate {
        enum { value = true };
    };

    template <typename T, typename U>
    struct b_false_predicate {
        enum { value = false };
    };

    template <typename U>
    using as_inner_1 = std::is_same<U, Inner1>;

    template <typename U>
    using as_inner_2 = std::is_same<U, Inner2>;

    template <typename U>
    using as_inner_3 = std::is_same<U, Inner3>;


};

} //testing
} //tl


