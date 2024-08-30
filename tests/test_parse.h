#ifndef TEST_PARSE_H
#define TEST_PARSE_H

#include <QDebug>
#include <QtTest>
#include <qt5/QtCore/qobject.h>
#include <qt5/QtCore/qobjectdefs.h>

class ParseTest : public QObject
{
    Q_OBJECT

private:
private slots:

    void initTestCase(); 
    void testSelectors();

};

#endif
