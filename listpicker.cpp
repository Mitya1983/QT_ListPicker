#include "listpicker.h"
#include <QDebug>
#include <QLayout>


ListPicker::ListPicker(int numberOfRowsShown, QWidget *parent) :
    QWidget(parent),
    layout(new QVBoxLayout(this)),
    labels(QVector<QLabel*>(numberOfRowsShown <= 0 ? numberOfRowsShown = 1 : (numberOfRowsShown % 2 == 0 ? --numberOfRowsShown : numberOfRowsShown))),
    selectedLabel(numberOfRowsShown / 2)
{
    circleItems = true;
    presentationSetup();
    _selectedIndex = 0;
    connect(this, &ListPicker::onSelectedValueChanged, this, &ListPicker::setShownValues);
    connect(this, &ListPicker::onMaxShownItemsChanged, this, &ListPicker::setShownValues);
}

void ListPicker::createList(const int &numberOfListElements, int startValue)
{
    if (list.size() != numberOfListElements)
    {
        list.resize(numberOfListElements);
    }
    for (auto i = 0; i < numberOfListElements; i++)
    {
        list[i] = QString::number(startValue++);
    }
    maxShownIndex = numberOfListElements - 1;
    setShownValues();
}

void ListPicker::createList(std::initializer_list<QString> _list)
{
    list = QVector<QString>(_list);
    maxShownIndex = list.size() - 1;
    setShownValues();
}

void ListPicker::createList(QVector<QString> &_vector)
{
    list = std::move(_vector);
    maxShownIndex = list.size() - 1;
    setShownValues();
}

void ListPicker::createList(QVector<QString> &&_vector)
{
    list = _vector;
    maxShownIndex = list.size() - 1;
    setShownValues();
}

void ListPicker::createList(QList<QString> &_list)
{
    list = QVector<QString>::fromList(std::move(_list));
    maxShownIndex = list.size() - 1;
    setShownValues();
}

void ListPicker::createList(QList<QString> &&_list)
{
    list = QVector<QString>::fromList(_list);
    maxShownIndex = list.size() - 1;
    setShownValues();
}

void ListPicker::setSelectedItem(int item)
{
    _selectedIndex = item - 1;
    emit onSelectedValueChanged(_selectedIndex);
}

QString ListPicker::selectedValue()
{
    return labels[selectedLabel]->text();
}

int ListPicker::selectedIndex()
{
    return _selectedIndex;
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
        _currentIndex = maxShownIndex;
    return _currentIndex;
}

int ListPicker::nextIndex(int _currentIndex)
{
    if (_currentIndex < maxShownIndex)
        ++_currentIndex;
    else
        _currentIndex = 0;
    return _currentIndex;
}

void ListPicker::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0)
    {
        upCount += event->delta();
        if (upCount >= 80)
        {
            if (_selectedIndex >= 0)
                _selectedIndex--;
            if (_selectedIndex < 0)
                _selectedIndex = maxShownIndex;
            upCount = 0;
            emit onSelectedValueChanged(_selectedIndex);
        }
    }
    if (event->delta() < 0)
    {
        downCount -= event->delta();
        if (downCount >= 80)
        {
            if (_selectedIndex <= maxShownIndex)
                _selectedIndex++;
            if (_selectedIndex > maxShownIndex)
                _selectedIndex = 0;
            downCount = 0;
            emit onSelectedValueChanged(_selectedIndex);
        }
    }
    event->accept();
}

void ListPicker::mousePressEvent(QMouseEvent *event)
{
    currentCursorXPos = event->pos().x();
}

void ListPicker::mouseMoveEvent(QMouseEvent *event)
{
    if ((geometry().contains(QCursor::pos())) && (event->buttons() & Qt::LeftButton))
    {
        if (event->pos().y() < currentCursorXPos)
        {
            upCount += 2;
            if  (upCount >= height() / maxShownIndex)
            {
                currentCursorXPos = event->pos().y();
                if (_selectedIndex <= maxShownIndex)
                    _selectedIndex++;
                if (_selectedIndex > maxShownIndex)
                    _selectedIndex = 0;
                upCount = 0;
                emit onSelectedValueChanged(_selectedIndex);
            }
        }
        if (event->pos().y() > currentCursorXPos)
        {
            downCount += 2;
            if (downCount >= height() / maxShownIndex)
            {
                currentCursorXPos = event->pos().y();
                if (_selectedIndex >= 0)
                    _selectedIndex--;
                if (_selectedIndex < 0)
                    _selectedIndex = maxShownIndex;
                downCount = 0;
                emit onSelectedValueChanged(_selectedIndex);
            }
        }
    }
}

void ListPicker::setShownValues(int _currentValueIndex)
{
    int listLastIndex = list.size() - 1;
    _currentValueIndex > listLastIndex ? _currentValueIndex = listLastIndex : _currentValueIndex;
    _currentValueIndex > maxShownIndex ? _currentValueIndex = maxShownIndex : _currentValueIndex;
    _currentValueIndex < 0 ? _currentValueIndex = 0 : _currentValueIndex;
    if (circleItems)
    {
        labels[selectedLabel]->setText(list[_currentValueIndex]);
        int pr_index = previousIndex(_currentValueIndex);
        for (int i = selectedLabel - 1; i >= 0; i--)
        {
            labels[i]->setText(list[pr_index]);
            pr_index = previousIndex(pr_index);
        }
        int nt_index = nextIndex(_currentValueIndex);
        for (int i = selectedLabel + 1, k = labels.size(); i < k; i++)
        {
            labels[i]->setText(list[nt_index]);
            nt_index = nextIndex(nt_index);
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
        if (_currentValueIndex <= listLastIndex)
            nt_index = _currentValueIndex + 1;
        for (int i = selectedLabel + 1, k = labels.size(); i < k; i++)
        {
            if (nt_index <= listLastIndex)
            {
                labels[i]->setText(list[nt_index]);
                nt_index++;
            }
            else
                labels[i]->setText("");
        }
    }
}

void ListPicker::setMaxShownItems(const int &_value)
{
    maxShownIndex = _value - 1;
    emit onMaxShownItemsChanged(_selectedIndex);
}


ListPicker::~ListPicker()
{
    std::for_each(labels.begin(), labels.end(), [] (QLabel *p) {delete p;});
}
