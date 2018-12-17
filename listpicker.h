#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QList>
#include <QFont>
//Reimplement maxDays on base of not to change the vector sizes but to limit the circle or shown rows.
//That is vector is always created with 31 days but shown days are limited.

enum class ListTypes
{
    Days,
    Months,
    Years,
    CustomNumbers, //For custom number list
    CustomString //For custom list of strings
};

class ListPicker : public QWidget
{
    Q_OBJECT

public:
    ListPicker(QWidget *parent = nullptr) = delete;
    ListPicker(ListTypes type,
               const int &numberOfRowsShown = 5,
               QWidget *parent = nullptr);



    ~ListPicker() override = default;
private:
    //Should list be circled
    bool circleItems;
    void setCircling(bool _val); //Setting circling
    bool isCircled(); //Checking if circled

    //Items storage
    QVector<QString> listOfStrings; //Stores items
    void createCustomNumberList(const int &_numbers); //creates custom number list
    void createCustomStringList(const QVector<QString> &_vector);
    void createCustomStringList(const QList<QString> &_list);
    //Maximum number of elements in list
    int maxShownItems;
    //Currently selected item
    int selectedItem;

    QString selectedItemToString(); //Getting selected value in string format

    //Functions used to set previous and next items
    int previousIndex(int _curentIndex);
    int nextIndex(int _curentIndex);

    //Scroling
    int upCount = 0, downCount = 0; //Used for scroll accumulation
    int currentCursorXPos = 0; //Used to store initital mouse cursor x position
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:

    //Default items initialisation and fillment (for days, months and years)
    void createDays(int _days); //Fills vector with days values (31)
    void createMonths(); // Fills vector with months values
    void createYears(); // Fills vector with yers values (by default current year - 70)

    //Sets shown rows
    void setShownValues(int _currentValueIndex);

signals:

    //Used to invoke createDays each time when maxDay is changed (changing 28, 29, 30 and 31 days count)
    void onMaxDayChanged(int newMaxDayValue);

    //Used to invoke setDayesShown
    void onSelectedValueChanged(int newSelectedValueIndex);

public slots:

    //Setting maximum of shown items
    void setMaxShownItems(const int &month, const int &year); //This function is implemented for days shown
    void setMaxShownItems(const int &_value); //This function is for custom limitation
};

#endif // WIDGET_H
