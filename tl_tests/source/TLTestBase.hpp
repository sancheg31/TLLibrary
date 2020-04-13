#pragma once

#include <string>
#include <map>

#include "source/TLfwd.hpp"

namespace TL {
namespace testing {

class TLTestBase {
protected:

    using container_type = std::multimap<std::string, TLTestBase*>;

    TLTestBase(const std::string& name) {
        listOfTests().emplace(name, this);
    }

    using zero_list = TL::type_list<>;

    using one_list = TL::type_list<int>;
    using one_list_1 = int;

    using integrals = TL::type_list<char, short, int, long>;
    using integrals_1 = char;
    using integrals_2 = short;
    using integrals_3 = int;
    using integrals_4 = long;

    using doubles = TL::type_list<float, double>;
    using doubles_1 = float;
    using doubles_2 = double;

    virtual void executeTrue() = 0;
    virtual void executeFalse() = 0;

    static container_type& listOfTests() {
        return listOfTests_;
    }

private:
    static container_type listOfTests_;
};

} //testing
} //tl
