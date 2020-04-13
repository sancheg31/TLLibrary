
#include "TLTestBase.hpp"

namespace TL {
namespace testing {

    TLTestBase::container_type TLTestBase::listOfTests_{};

    TLTestBase::TLTestBase(const std::string& name) {
        TLTestBase::listOfTests().emplace(name, this);
    }

    auto TLTestBase::listOfTests() -> container_type& {
        return listOfTests_;
    }

} //testing
} //tl

