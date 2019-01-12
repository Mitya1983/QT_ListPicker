#ifndef LISTPICKER_H
#define LISTPICKER_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QList>
#include <QFont>
#include <QVBoxLayout>

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
    //Parent widget should be specified in constructor. Nullptr is not possible. Because list presentation is based on parent widget height.
    //Passed number should be odd, otherwise passed value will be decremented to nearest odd one
    //If zero is passed the number of shown rows will be calculated on base of widget height
    ListPicker(QWidget *parent, int numberOfRowsShown = 0);
    //Calculating number of rows
    int numberOfLabels(int parentHeight);

    //List creation. One of the createList function should be invoked before adding or showing widget.
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

public slots:

    //Setting maximum of shown items (Useful if number of shown items should be limited depending on some circumstances)
    //For example: days should be decreased/increased depending on month selected
    void setMaxShownItems(const int &_value);

private: /*Methods*/

    //Seting up the layout
    void presentationSetup(int parentHeight);
    //Sizing the labels according to widget size
    void labelsSizing(int parentHeight);

    //Functions used to set previous and next items
    int previousIndex(int _curentIndex);
    int nextIndex(int _curentIndex);

    //Scroling
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    //Resizing labels
    void resizeEvent(QResizeEvent *event) override;

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

#endif // LISTPICKER_H
