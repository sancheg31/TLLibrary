#include <QtTest>

// add necessary includes here

class one_two_three : public QObject
{
    Q_OBJECT

public:
    one_two_three();
    ~one_two_three();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

one_two_three::one_two_three()
{

}

one_two_three::~one_two_three()
{

}

void one_two_three::initTestCase()
{

}

void one_two_three::cleanupTestCase()
{

}

void one_two_three::test_case1()
{

}

QTEST_APPLESS_MAIN(one_two_three)

#include "tst_one_two_three.moc"
