
#include "TLTestBase.hpp"

namespace TL {
namespace testing {


    TLTestBase::TLTestBase(const std::string& name) {
        listOfTests().emplace(name, this);
    }

    TLTestBase::container_type& TLTestBase::listOfTests() {
        return listOfTests_;
    }

} //testing
} //tl

