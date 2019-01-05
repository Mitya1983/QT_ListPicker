#ifndef LISTPICKER_H
#define c_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QList>
#include <QFont>
#include <QVBoxLayout>


class ListPicker : public QWidget
{
    Q_OBJECT

public: 
    //Number of shown items in the widget one selected item
    //5 is by default. Passed number should be odd, otherwise passed value will be decremented to nearest odd one
    ListPicker(int numberOfRowsShown = 5,
               QWidget *parent = nullptr);

    void createList(const int &numberOfListElements, int startValue); //Creating list starting from startValue
    void createList(std::initializer_list<QString> _list); //Creating list using initializer list
    //Creating list from existing vector
    void createList(QVector<QString> &_vector);
    void createList(QVector<QString> &&_vector);
    //Creating list from existing list
    void createList(QList<QString> &_list);
    void createList(QList<QString> &&_list);

    void setSelectedItem(int item);
    QString selectedValue(); //Getting value of the selected item
    int selectedIndex(); //Getting index of the selected item
    void setCircling(bool val); //Setting circling

public slots:

    //Setting maximum of shown items
    void setMaxShownItems(const int &_value);

private:
    QVBoxLayout *layout;
    QVector<QLabel*> labels; //Labels to show rows
    int selectedLabel;
    void presentationSetup();

    //Should list be circled
    bool circleItems;
    bool isCircled(); //Checking if circled

    //Items storage
    QVector<QString> list; //Stores items
    //Maximum number of elements in list
    int maxShownIndex;
    //Currently selected item
    int _selectedIndex;

    //Functions used to set previous and next items
    int previousIndex(int _curentIndex);
    int nextIndex(int _curentIndex);

    //Scroling
    int upCount = 0, downCount = 0; //Is used for scroll accumulation
    int currentCursorXPos = 0; //Is used to store initital mouse cursor x position
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:

    //Sets shown rows
    void setShownValues(int _currentValueIndex = 0);

signals:

//    Used to invoke createDays each time when maxDay is changed (changing 28, 29, 30 and 31 days count)
    void onMaxShownItemsChanged(int maxShownIndex);

//    Used to invoke setShownValues
    void onSelectedValueChanged(int newSelectedValueIndex);

public:
    ~ListPicker() override;
};

#endif // WIDGET_H
