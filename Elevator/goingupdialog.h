#ifndef GOINGUPDIALOG_H
#define GOINGUPDIALOG_H

#include <QDialog>
#include <QElapsedTimer>
//#include "goingdowndialog.h"
#include "queue.h"
using namespace queue;

class GoingDownDialog;

namespace Ui {
class GoingUpDialog;
}

class GoingUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GoingUpDialog(QWidget *parent = 0);
    ~GoingUpDialog();    // destructor

    void array_read(int s[], int f); // reads an array
    void set_current_floor(int f); // needs to be public to be implemented in the Main Window
//    void get_array(int s[]);

// for the buttons
private slots:
    void on_pushButton_clicked(); // first floor
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked(); // tenth floor

    void on_pushButton_11_clicked(); // close door
    void on_pushButton_12_clicked(); // open door

private:
    Ui::GoingUpDialog *ui; // points to data created on the heap
    Queue *queueUp; // queue list
    int current_floor;  // increments the count
    int selected_floor;
    string selected_floor_message(int f);
    string total_people_to_floor_message(int f);
    string current_floor_message(int f);
    enum Floor{first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, tenth};
    void delay(); // delays program to simulate doors opening and closing

    bool open_door; // if it's true, can't open door, otherwise, they are allowed to keep doors open

    QElapsedTimer *timer;

    const int MAX_FLOORS = 10;
    const int MAX_CAPACITY = 15;

    GoingDownDialog *goingdowndialog;

    int *a; // dynamic array
    void array_constructor();
    int array_total();
    void array_delete();

};

#endif // GOINGUPDIALOG_H
