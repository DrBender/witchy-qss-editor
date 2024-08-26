#include <iostream>
#include <QApplication>
#include "MainWindow.h"

using namespace std;


int main(int argc, char *argv[])
{
    QApplication app (argc, argv);

    QCoreApplication::setApplicationName("Witchy Qss Editor");
    cout << "Qss Editor" << endl;
    
    MainWindow w;
    w.show();

    return app.exec();
}
