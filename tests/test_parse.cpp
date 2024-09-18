#include <QDebug>
#include <QTest>
#include <qtestcase.h>

#include "../editor/Parser.h"


class ParseTest : public QObject
{
    Q_OBJECT

private slots:

    void initTestCase(); 
    void testSelectors();

};

void ParseTest::initTestCase()
{
    qDebug() << "Init Test Case";
    qDebug() << "Test";
}
void ParseTest::testSelectors()
{
    QCOMPARE(5, 5);
    Parser p;
    QString str = "QProgressBar{}";
    p.parse(str);
    QVERIFY(p.parsed_text == "QProgressBar {\n}\n\n");
}

QTEST_APPLESS_MAIN(ParseTest)
#include "test_parse.moc"
