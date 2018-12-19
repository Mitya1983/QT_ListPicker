#ifndef LISTPICKER_H
#define c_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QList>
#include <QFont>
#include <QVBoxLayout>

//Reimplement maxDays on base of not to change the vector sizes but to limit the circle or shown rows.
//That is vector is always created with 31 days but shown days are limited.

class ListPicker : public QWidget
{
    Q_OBJECT

public:
//    ListPicker(QWidget *parent = nullptr);
    ListPicker(QWidget *parent = nullptr,
               const int &numberOfRowsShown = 5); //Number of shown items in th widget one selected item in the middle and -+items (2 by default)
    ListPicker(const int &numberOfListElements, //Size of a list
               QWidget *parent = nullptr,
               const int &numberOfRowsShown = 5);
    ListPicker(std::initializer_list<QString> _list, //Creates list from string values passed to list
               QWidget *parent = nullptr,
               const int &numberOfRowsShown = 5);

    void createList(const int &numberOfListElements, const int &startValue); //Creates custom number list starting from startValue
    void createList(std::initializer_list<QString> list);
    void createStringList(const QVector<QString> &_vector); //Creates custom string list from existing vector
    void createStringList(const QList<QString> &_list); //Creates custom string list from existing list

    QString selectedValue(); //Getting value of the selected item
    int selectedIndex(); //Getting index of the selected item

    ~ListPicker() override;
private:
    void presentationSetup();
    QVBoxLayout *layout;
    QVector<QLabel*> labels; //Labels to show rows
    int selectedLabel;

    //Should list be circled
    bool circleItems;
    void setCircling(bool _val); //Setting circling
    bool isCircled(); //Checking if circled

    //Items storage
    QVector<QString> list; //Stores items
    //Maximum number of elements in list
    int maxShownItems;
    //Currently selected item
    int _selectedIndex;

    //Functions used to set previous and next items
    int previousIndex(int _curentIndex);
    int nextIndex(int _curentIndex);

    //Scroling
    int upCount = 0, downCount = 0; //Is used for scroll accumulation
    int currentCursorXPos = 0; //Is used to store initital mouse cursor x position
//    void wheelEvent(QWheelEvent *event) override;
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseMoveEvent(QMouseEvent *event) override;

private slots:

    //Sets shown rows
    //void setShownValues(int _currentValueIndex);

signals:

    //Used to invoke createDays each time when maxDay is changed (changing 28, 29, 30 and 31 days count)
//    void onMaxShownItemsChanged(int maxShownItems);

    //Used to invoke setDayesShown
//    void onSelectedValueChanged(int newSelectedValueIndex);

public slots:

    //Setting maximum of shown items
  //  void setMaxShownItems(const int &_value);
};

#endif // WIDGET_H
