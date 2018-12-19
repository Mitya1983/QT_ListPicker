#include "listpicker.h"
#include <QDebug>
#include <QLayout>


ListPicker::ListPicker(QWidget *parent, const int &numberOfRowsShown) :
    QWidget(parent),
    layout(new QVBoxLayout(this)),
    labels(QVector<QLabel*>(numberOfRowsShown)),
    selectedLabel(numberOfRowsShown / 2)
{
    presentationSetup();
}

ListPicker::ListPicker(const int &numberOfListElements, QWidget *parent, const int &numberOfRowsShown) :
    QWidget (parent),
    layout(new QVBoxLayout(this)),
    labels(QVector<QLabel*>(numberOfRowsShown)),
    selectedLabel(numberOfRowsShown / 2)
{
    presentationSetup();
    list = QVector<QString>(numberOfListElements);
}

ListPicker::ListPicker(std::initializer_list<QString> _list, QWidget *parent, const int &numberOfRowsShown) :
    QWidget (parent),
    layout(new QVBoxLayout(this)),
    labels (QVector<QLabel*>(numberOfRowsShown)),
    selectedLabel(numberOfRowsShown / 2)
{
    presentationSetup();
    list = QVector<QString>(_list);
}

ListPicker::~ListPicker()
{
    std::for_each(labels.begin(), labels.end(), [] (QLabel *p) {delete p;});
}

void ListPicker::presentationSetup()
{
    layout->setSpacing(0);
    int fontDecrement = 4;
    setContentsMargins(0, 0, 0, 0);
    for (int i = 0, k = labels.size(); i < k; i ++)
    {
        labels[i] = new QLabel(this);
        labels[i]->setText("TEST");
        labels[i]->setAlignment(Qt::AlignCenter);
        QFont font = labels[i]->font();
        font.setBold(true);
        i == selectedLabel ? labels[i]->setEnabled(true) : labels[i]->setEnabled(false);
        i <= selectedLabel ? font.setPointSize(labels[i]->height() - (fontDecrement + (fontDecrement * (selectedLabel - i)))) :
                            font.setPointSize(labels[i]->height() - (fontDecrement + (fontDecrement * (i - selectedLabel))));
        labels[i]->setFont(font);
        layout->addWidget(labels[i]);
    }
    this->setLayout(layout);
}
