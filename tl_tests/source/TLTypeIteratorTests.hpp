#pragma once

#include "TLTestBase.hpp"
#include "TLTestCase.hpp"

#include "source/TLfwd.hpp"
#include "source/TLMetaFunctionGenerators.hpp"
#include "source/TLTraits.hpp"
#include "source/TLTypeIterator.hpp"

namespace TL {
namespace testing {

/**
 *  Static Assertions:
 *      iterator outside the scope is a compilation error.
 *
 * */


class TLTypeIteratorTests: public ::testing::Test, public TLTestBase
{
protected:
    TL_HAS_NESTED_TYPE(value)
    TL_HAS_NESTED_TYPE(list)
    TL_HAS_NESTED_TYPE(prev)
    TL_HAS_NESTED_TYPE(next)
    TL_HAS_NESTED_TEMPLATE_TYPE(set_value)

    template <std::size_t I>
    using empty_iter = type_iterator<empty_list, I>;
    template <std::size_t I>
    using single_iter = type_iterator<singleton_list, I>;
    template <std::size_t I>
    using int_iter = type_iterator<integrals, I>;
    template <std::size_t I>
    using double_iter = type_iterator<doubles, I>;

};

} //testing
} //tl



