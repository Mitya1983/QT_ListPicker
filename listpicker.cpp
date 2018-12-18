#include "listpicker.h"
#include <QDebug>
#include <QLayout>


ListPicker::ListPicker(QWidget *parent, const int &numberOfRowsShown) :
    QWidget(parent),
    layout(new QVBoxLayout(this)),
    labels(QVector<QLabel*>(numberOfRowsShown)),
    centralLabel(numberOfRowsShown / 2)
{

    for (int i = 0; i < numberOfRowsShown; i ++)
    {
        labels[i] = new QLabel(this);
        labels[i]->setText("TEST");
        labels[i]->setAlignment(Qt::AlignCenter);
        QFont font = labels[i]->font();
        font.setBold(true);
        if (i == centralLabel)
        {
            font.setPointSize(labels[i]->height() - 2);
        }
        else if (i == centralLabel - 1 || i == centralLabel + 1) {
            font.setPointSize(labels[i]->height() - 5);
            labels[i]->setEnabled(false);
        }
        else {
            font.setPointSize(labels[i]->height() - 8);
            labels[i]->setEnabled(false);
        }
        labels[i]->setFont(font);
        layout->addWidget(labels[i]);
    }
    this->setLayout(layout);
    list = QVector<QString>(5);
}

ListPicker::~ListPicker()
{
    std::for_each(labels.begin(), labels.end(), [] (QLabel *p) {delete p;});
}
