#ifndef GOINGDOWNDIALOG_H
#define GOINGDOWNDIALOG_H


#include <QDialog>
#include <QElapsedTimer>
#include <iostream>
//#include "goingupdialog.h"
#include "stack.h"
using namespace std;
using namespace stack;

class GoingUpDialog; // forward declaration

namespace Ui {
class GoingDownDialog;
}

class GoingDownDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GoingDownDialog(QWidget *parent = 0);
    ~GoingDownDialog();

    void set_current_floor(int f); // needs to be public to be implemented in the Main Window
    void array_read(int s[], int f);
//    void get_array(int s[]);


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();

private:
    Ui::GoingDownDialog *ui;
    Stack *stackDown; // queue list
    int current_floor;  // increments the count
    int selected_floor;
    string selected_floor_message(int f);
    string total_people_to_floor_message(int f);
    string current_floor_message(int f);
    enum Floor{first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, tenth};
    void delay(); // delays program to simulate doors opening and closing

    bool open_door; // if it's true, can't open door, otherwise, they are allowed to keep doors open
//    bool from_array;

    const int MAX_FLOORS = 10;
    const int MAX_CAPACITY = 15;

    QElapsedTimer *timer;

    GoingUpDialog *goingupdialog;

    int *a; // dynamic array
    void array_constructor();
    int array_total();
    void array_delete();


};




#endif // GOINGDOWNDIALOG_H
