#pragma once

#include <QtTest>
#include <QtTest/QtTest>

#include <QObject>
#include <QString>
#include <QVector>

#include "source/type_list.h"

namespace TL {

class TestSuite: public QObject
{
    Q_OBJECT
public:
    explicit TestSuite(const QString& test = "");
    static QVector<TestSuite*>& testList();
    virtual ~TestSuite();

private:
    static QVector<TestSuite*> instance;
    QString testName;


};

} //tl
