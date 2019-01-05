#ifndef LISTPICKER_H
#define c_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QList>
#include <QFont>
#include <QVBoxLayout>
//TODO: Implement overlap view mode
//      Implement calculation of number of rows depending on widget height
//      Setup mouse move to be related to widget size and not to maxShownIndex

class ListPicker : public QWidget
{
    Q_OBJECT
private: /*Members*/

    //Main layout for placing labels
    QVBoxLayout *_layout;
    //Labels to show rows
    QVector<QLabel*> labels;
    //Central label
    int selectedLabel;
    //Indicates whether list shoud be shown circle like
    bool circleItems;
    //Indicates whether labels shoud be plavced with overlap or not (Selected label in front of other ones)
    bool overlapLabels;
    //Items storage
    QVector<QString> list;
    //Maximum number of elements in list
    int maxShownIndex;
    //Currently selected index
    int _selectedIndex;

    //Scroll members:
    //Is used for scroll accumulation
    int upCount = 0, downCount = 0;
    //Is used to store initital mouse cursor x position
    int currentCursorXPos = 0;

public: /*Methods*/

    //Passed number should be odd, otherwise passed value will be decremented to nearest odd one
    //If aero is passed the number of shown rows will be calculated on base of widget width (not yet implemented - one is instead)
    ListPicker(int numberOfRowsShown = 1,
               QWidget *parent = nullptr);

    //Creating list of numbers starting from startValue
    void createList(const int &numberOfListElements, int startValue);
    //Creating list using initializer list
    void createList(std::initializer_list<QString> _list);
    //Creating list from existing vector
    void createList(QVector<QString> &_vector);
    void createList(QVector<QString> &&_vector);
    //Creating list from existing list
    void createList(QList<QString> &_list);
    void createList(QList<QString> &&_list);
    //Setting selected item
    void setSelectedItem(int item);
    //Getting value of the selected item
    QString selectedValue();
    //Getting index of the selected item
    int selectedIndex();
    //Setting circling (true by default)
    void setCircling(bool val);
    bool isCircled(); //Checking if circled
    //Setting overlaping (false on default)
    void setOverlap(bool val);

public slots:

    //Setting maximum of shown items (Useful if number of shown items should be limited depending on some circumstances)
    //For example: days should be decreased/increased depending on month selected
    void setMaxShownItems(const int &_value);

private: /*Methods*/

    //Seting up the layout
    void presentationSetup();

    //Functions used to set previous and next items
    int previousIndex(int _curentIndex);
    int nextIndex(int _curentIndex);

    //Scroling
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:

    //Sets shown rows
    void setShownValues(int _currentValueIndex = 0);

signals:

    //Is emited if setMaxShownItems was invoked
    void onMaxShownItemsChanged(int maxShownIndex);

    //Is emited if _selectedItem had changed either by setSelectedItem function or Scroll event
    void onSelectedValueChanged(int newSelectedValueIndex);

public: /*Destructor*/
    ~ListPicker() override;
};

#endif // WIDGET_H
