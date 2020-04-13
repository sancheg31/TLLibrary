#pragma once


#include "source/TLfwd.hpp"

namespace TL {
namespace testing {

class TLTestBase {
protected:
    using zero_list = TL::type_list<>;

    using int_list = TL::type_list<int>;
    using int_list_1 = int;

    using integrals = TL::type_list<char, short, int, long>;
    using integrals_1 = char;
    using integrals_2 = short;
    using integrals_3 = int;
    using integrals_4 = long;

    using doubles = TL::type_list<float, double>;
    using doubles_1 = float;
    using doubles_2 = double;

    virtual void execute() = 0;
};

} //testing
} //tl
