#pragma once

#include <gtest/gtest.h>

#include "TLTestBase.hpp"
#include "TLTestCase.hpp"
#include "source/TLMetaFunctionGenerators.hpp"

namespace TL {
namespace testing {

class TLTypeIteratorOperationsTests: public ::testing::Test, public TLTestBase
{
protected:
    TL_HAS_NESTED_TYPE(result)
    TL_HAS_NESTED_VALUE(result)
};

} //testing
}//tl

