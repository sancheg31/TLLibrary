#pragma once

#include <gtest/gtest.h>

#include "source/TLfwd.hpp"

namespace TL {
namespace testing {

class TLTestBase {

protected:

    using empty_list = TL::type_list<>;
    constexpr static std::size_t empty_list_size = 0;

    using singleton_list = TL::type_list<int>;
    using singleton_0 = int;

    constexpr static std::size_t singleton_list_size = 1;

    using integrals = TL::type_list<char, short, int, long>;
    using integrals_0 = char;
    using integrals_1 = short;
    using integrals_2 = int;
    using integrals_3 = long;
    constexpr static std::size_t integrals_size = 4;

    using doubles = TL::type_list<float, double>;
    using doubles_0 = float;
    using doubles_1 = double;
    constexpr static std::size_t doubles_size = 2;

};


} //testing
} //tl
