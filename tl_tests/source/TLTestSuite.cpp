
#include "TLTestSuite.hpp"


namespace TL {

QVector<TestSuite*> TestSuite::instance{};

TestSuite::TestSuite(const QString& test): QObject(), testName(test) {
    testList().push_back(this);
}

TestSuite::~TestSuite() { }

/*static*/ QVector<TestSuite*>& TestSuite::testList() {
    return instance;
}

} //tl
