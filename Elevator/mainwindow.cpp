/*
 Everything is run through the main window
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "windows.h"
//#include <time.h>
//#include <stdlib.h>     // srand() and rand()
#include <QTime>
#include <QTextStream>

#include <iostream>
using namespace std;

#include "goingupdialog.h"
#include "goingdowndialog.h"


// constructor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QPalette mainColor = this->palette();
    mainColor.setColor(this->backgroundRole(), Qt::lightGray);
    this->setAutoFillBackground(true);
    this->setPalette(mainColor);
    this->show();

    ui->setupUi(this);

    current_floor = 1;

//    a = new int[MAX_FLOORS];
}


// destructor
MainWindow::~MainWindow()
{
    delete ui;
}



// returns the floor where the user clicked from -- and increment from there
int MainWindow::get_current_floor()
{
    return current_floor;
}


// function that delays time -- better than using Sleep which only freezes the application
void MainWindow::delay()
{
    QTime dieTime = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


// going up button
void MainWindow::on_pushButton_clicked()
{
    ui->plainTextEdit->insertPlainText("Up elevator arrived");

    // pause
    delay();


    // once the up elevator has arrived, this background changes to green to indicate it's going up
    QPalette pal = this->palette();
    pal.setColor(this->backgroundRole(), Qt::green);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->show();


    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this,tr("Question"),tr("Go in?"));


    // for the pop-up question of whether the user wants to go into elevator
    if (reply == QMessageBox::Yes)
    {
        ui->plainTextEdit->clear();

        goingupdialog = new GoingUpDialog(this); // passing th eparent class
        goingupdialog->show(); // shows the new form
//        goingupdialog->exec();

        // setting the floor for the going up elevator
        goingupdialog->set_current_floor(current_floor);

        pal.setColor(this->backgroundRole(), Qt::lightGray);
        this->setAutoFillBackground(true);
        this->setPalette(pal);

        this->hide();

    }
    else
    {
        // if they select no, clear message
        ui->plainTextEdit->clear();

        // go back to gray background
        pal.setColor(this->backgroundRole(), Qt::lightGray);
        this->setAutoFillBackground(true);
        this->setPalette(pal);
    }

}

// bottom button
// change screen -- inside of elevator
void MainWindow::on_pushButton_2_clicked()
{

    ui->plainTextEdit->insertPlainText("Down elevator arrived");

    delay();

    QPalette pal = this->palette();
    pal.setColor(this->backgroundRole(), Qt::red);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->show();

//    ui->plainTextEdit->clear();


    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this,tr("Question"),tr("Go in?"));


    if (reply == QMessageBox::Yes)
    {
        ui->plainTextEdit->clear();

        goingdowndialog = new GoingDownDialog(this); // passing th eparent class

        goingdowndialog->set_current_floor(10);

        goingdowndialog->show();
//        goingdowndialog->exec();

        pal.setColor(this->backgroundRole(), Qt::lightGray);
        this->setAutoFillBackground(true);
        this->setPalette(pal);
//        goingdowndialog->show(); // shows the new form

        this->hide();

    }
    else // run different code to reset the elevator and wait times
    {
        ui->plainTextEdit->clear();

        pal.setColor(this->backgroundRole(), Qt::lightGray);
        this->setAutoFillBackground(true);
        this->setPalette(pal);
    }

}
