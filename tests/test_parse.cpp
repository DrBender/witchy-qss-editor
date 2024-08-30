#include "test_parse.h"
#include <qt5/QtCore/qglobal.h>

void ParseTest::initTestCase()
{
    qDebug() << "Init Test Case";
    qDebug() << "Test";
}
void ParseTest::testSelectors()
{
    QCOMPARE(5, 5);
    QCOMPARE(4, 5);
}

QTEST_MAIN(ParseTest)
#include "build/moc/test_parse.moc"
