#include "listpicker.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListPicker w;
    w.createList(10, 1);
    w.setSelectedItem(3);
    w.show();
    return a.exec();
}
