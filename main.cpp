#include "settings.h"
#include <QApplication>
#include <iostream>
#include "MainWindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("DrBender");
    QCoreApplication::setApplicationName("Witchy Qss Editor");

    cout << "Qss Editor" << endl;

    MainWindow w;
    w.show();

    return app.exec();
}
