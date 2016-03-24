

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "goingupdialog.h"
#include "goingdowndialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    int get_current_floor();
//    void get_pointer_to_array(int n[]);
    ~MainWindow();


private slots:
    void on_pushButton_clicked(); // going up
    void on_pushButton_2_clicked(); // going down

private:
    Ui::MainWindow *ui;
    GoingUpDialog *goingupdialog; // works in the heap memory
    GoingDownDialog *goingdowndialog;
    int current_floor;
    int *a; // pointer to a dynamic array (on heap)
    void delay();
    enum Floors{first,second,third,fourth,fifth,sixth,seventh,eighth,ninth,tenth};

//    const int MAX_FLOORS = 10;
  //      Floors elevator;
};

#endif // MAINWINDOW_H
