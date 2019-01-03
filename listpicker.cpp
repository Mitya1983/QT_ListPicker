#include "listpicker.h"
#include <QDebug>
#include <QLayout>


ListPicker::ListPicker(const int &numberOfRowsShown, QWidget *parent) :
    QWidget(parent),
    layout(new QVBoxLayout(this)),
    labels(QVector<QLabel*>(numberOfRowsShown)),
    selectedLabel(numberOfRowsShown / 2)
{
    circleItems = true;
    presentationSetup();
    createNumberList(100, 1);
    setShownValues();
}

ListPicker::ListPicker(const int &numberOfListElements, const int &numberOfRowsShown, QWidget *parent) :
    QWidget (parent),
    layout(new QVBoxLayout(this)),
    labels(QVector<QLabel*>(numberOfRowsShown)),
    selectedLabel(numberOfRowsShown / 2)
{
    circleItems = true;
    presentationSetup();
    list = QVector<QString>(numberOfListElements);
    maxShownItems = list.size();
}

ListPicker::ListPicker(std::initializer_list<QString> _list, const int &numberOfRowsShown, QWidget *parent) :
    QWidget (parent),
    layout(new QVBoxLayout(this)),
    labels (QVector<QLabel*>(numberOfRowsShown)),
    selectedLabel(numberOfRowsShown / 2)
{
    circleItems = true;
    presentationSetup();
    list = QVector<QString>(_list);
    maxShownItems = list.size();
}

void ListPicker::createNumberList(const int &numberOfListElements, int startValue)
{
    if (list.size() != numberOfListElements)
    {
        list.resize(numberOfListElements);
    }
    for (auto i = 0; i < numberOfListElements; i++)
    {
        list[i] = QString::number(startValue++);
    }
    maxShownItems = numberOfListElements;
}

QString ListPicker::selectedValue()
{
    return labels[selectedLabel]->text();
}


void ListPicker::presentationSetup()
{
    layout->setSpacing(0);
    int fontDecrement = 4;
    setContentsMargins(0, 0, 0, 0);
    for (int i = 0, k = labels.size(); i < k; i ++)
    {
        labels[i] = new QLabel(this);
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

void ListPicker::setCircling(bool val)
{
    circleItems = val;
}

int ListPicker::previousIndex(int _currentIndex)
{
    if (_currentIndex > 0)
        --_currentIndex;
    else
        _currentIndex = maxShownItems - 1;
    return _currentIndex;
}

int ListPicker::nextIndex(int _currentIndex)
{
    if (_currentIndex < maxShownItems - 1)
        ++_currentIndex;
    else
        _currentIndex = 0;
    return _currentIndex;
}

void ListPicker::setShownValues(int _currentValueIndex)
{
    if (circleItems)
    {
        labels[selectedLabel]->setText(list[_currentValueIndex]);
        int pr_index = previousIndex(_currentValueIndex);
        for (int i = selectedLabel - 1; i >= 0; i--)
        {
            labels[i]->setText(list[pr_index]);
            pr_index--;
        }
        int nt_index = nextIndex(_currentValueIndex);
        for (int i = selectedLabel + 1, k = labels.size(); i < k; i++)
        {
            labels[i]->setText(list[nt_index]);
            nt_index++;
        }
    }
    else
    {
        labels[selectedLabel]->setText(list[_currentValueIndex]);
        int pr_index = 0, nt_index = 0;
        if (_currentValueIndex >= 0)
            pr_index = _currentValueIndex - 1;
        for (int i = selectedLabel - 1; i >= 0; i--)
        {
            if (pr_index >= 0)
            {
                labels[i]->setText(list[pr_index]);
                pr_index--;
            }
            else
                labels[i]->setText("");
        }
        if (_currentValueIndex < list.size())
            nt_index = _currentValueIndex + 1;
        for (int i = selectedLabel + 1, k = labels.size(); i < k; i++)
        {
            if (nt_index < list.size())
            {
                labels[i]->setText(list[nt_index]);
                nt_index++;
            }
            else
                labels[i]->setText("");
        }
    }
}





ListPicker::~ListPicker()
{
    std::for_each(labels.begin(), labels.end(), [] (QLabel *p) {delete p;});
}
