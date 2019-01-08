#include "listpicker.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListPicker w(3);
    w.createList(100, 1);
    w.show();
    return a.exec();
}
