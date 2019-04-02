//ToDo2014 <QtGui/QApplication>
#include <QApplication>
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setWindowTitle("Implicit FDM");
    w.setFixedWidth(300);
    w.show();
    return a.exec();
}
