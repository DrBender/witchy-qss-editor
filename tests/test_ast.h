

#include "qobject.h"
#include "qobjectdefs.h"
#include <QDebug>


class TestAST : public QObject
{
Q_OBJECT
    private:
    private slots:
    void initTestCase()
    {
        qDebug() << "Init TestAST";
    }

    void testSelectorAST()
    {
        
    }

};
