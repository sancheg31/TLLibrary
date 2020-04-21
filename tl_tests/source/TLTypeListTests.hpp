#pragma once

#include <gtest/gtest.h>

#include "TLTestBase.hpp"

namespace TL {
namespace testing {

class TLTypeListTests: public ::testing::Test, public TLTestBase
{
protected:
    struct Inner1 { }; struct Inner2 { }; struct Inner3 { };
    using list_1_2_3 = type_list<Inner1, Inner2, Inner3>;
    using list_1_1_1 = type_list<Inner1, Inner1, Inner1>;
    using list_2_1_2 = type_list<Inner2, Inner1, Inner2>;
    using list_3_2_3 = type_list<Inner3, Inner2, Inner3>;
    using list_1_1 = type_list<Inner1, Inner1>;
    using list_2_1 = type_list<Inner2, Inner1>;
    using list_3_2 = type_list<Inner3, Inner2>;
    using list_1_2 = type_list<Inner1, Inner2>;
    using list_2_3 = type_list<Inner2, Inner3>;
    using list_1 = type_list<Inner1>;
    using list_2 = type_list<Inner2>;
    using list_3 = type_list<Inner3>;
};

} //testing
} //tl


