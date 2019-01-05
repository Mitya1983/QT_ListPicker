#include "listpicker.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListPicker w(9);
    w.createList(10, 1);
    w.show();
    return a.exec();
}
