#pragma once

#include "TLTestBase.hpp"
#include "TLTestCase.hpp"

#include "source/TLfwd.hpp"
#include "source/TLMetaFunctionGenerators.hpp"
#include "source/TLTraits.hpp"
#include "source/TLIterator.hpp"

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
    GENERATE_TYPE_PROPERTY_METAFUNCTION(value)
    GENERATE_TEMPLATE_TYPE_PROPERTY_METAFUNCTION(set_value)

    GENERATE_TYPE_PROPERTY_METAFUNCTION(list)
    GENERATE_TYPE_PROPERTY_METAFUNCTION(next)
    GENERATE_TYPE_PROPERTY_METAFUNCTION(prev)

    template <std::size_t I>
    using empty_iter = type_iterator<empty_list, I>;
    template <std::size_t I>
    using single_iter = type_iterator<singleton_list, I>;
    template <std::size_t I>
    using int_iter = type_iterator<integrals, I>;
    template <std::size_t I>
    using double_iter = type_iterator<doubles, I>;

    template <typename T, typename U>
    static constexpr bool is_same_v = std::is_same<T, U>::value;

};

} //testing
} //tl



