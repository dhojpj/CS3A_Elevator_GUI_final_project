#include "goingdowndialog.h"
#include "ui_goingdowndialog.h"

#include <QPalette>
#include "windows.h"
#include <sstream>
#include <QString>
#include <QTime>
#include <QElapsedTimer>
#include <QMessageBox>
#include "goingupdialog.h"
#include <QDebug>
#include <iostream>
#include "stack.h"
using namespace std;

using namespace stack;



GoingDownDialog::GoingDownDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoingDownDialog)
{


    QPalette pal = this->palette();
    pal.setColor(this->backgroundRole(), Qt::red);
    this->setPalette(pal);

    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
//    Qt::WA_DeleteOnClose();
    current_floor = MAX_FLOORS;
    open_door = true;

    // creating stack object on the heap
    stackDown = new Stack;

    // decrementing floors
    for (int i = 1; i < MAX_FLOORS; i++)
    {
//        qDebug() << "construct floor = " << i << endl;
        stackDown->push(i, 0);
    }


    array_constructor();

}

GoingDownDialog::~GoingDownDialog()
{
//    delete [] a;
//    a = NULL;
//    delete stackDown;
//    stackDown = NULL;
    delete ui;
}


// multi selection increments manually for their respective nodes and tallies total
void GoingDownDialog::set_current_floor(int f)
{
    current_floor = f;

    stringstream ss;
    ss << "Floor #" << current_floor << endl;
    string s = ss.str();

    ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable


}




// function that delays time -- better than using Sleep which only freezes the application
void GoingDownDialog::delay()
{
    QTime dieTime = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}





// returns a string for the button selections
string GoingDownDialog::selected_floor_message(int f)
{
    stringstream ss;

    ss << "Floor #" << f << " was selected" << endl;

    return ss.str();
}


// returns a string for the button selections
string GoingDownDialog::total_people_to_floor_message(int f)
{
    stringstream ss;

    if (stackDown->get_people(f) == 1)
    {
        ss << stackDown->get_people(f) << " person going to Floor #" << f << endl;
    }
    else
    {
        ss << stackDown->get_people(f) << " people going to Floor #" << f << endl;
    }

    return ss.str();
}

// returns message of what floor they're on/passing by
string GoingDownDialog::current_floor_message(int f)
{
    stringstream ss;

    ss << "Elevator is currently at Floor #" << f << endl;

    return ss.str();
}


// prompt how many persons select that floor
// tally up total people on floor
    // add new people later going up
// close elevator -- true/false boolian
// increment floor
// subtract people









// first floor button -- save the number of people who want to go down (when current_floor > 1)
void GoingDownDialog::on_pushButton_clicked()
{
    string s;

    if (open_door)
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        selected_floor = first + 1;
        s = selected_floor_message(selected_floor);
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    else
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        s = "Error. Must 'Open' Door before selecting\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }


    if (stackDown->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor > selected_floor && open_door && array_total() + stackDown->total_people() < MAX_CAPACITY)
    {
        stackDown->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is higher than the current one, wait
    else if (selected_floor > current_floor && open_door && stackDown->total_people() + array_total() < MAX_CAPACITY)
    {
        a[selected_floor - 1] += 1;
        stringstream ss;
        string s;

        ss << a[selected_floor - 1] << " people will later go to Floor #" << selected_floor << endl << endl;
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }

//    if (open_door && array_total() + stackDown->total_people() == MAX_CAPACITY)
//    {
//        delay();
//        ui->plainTextEdit->clear();
//        string s = "Elevator at Max Capacity\n\n";
//        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
//    }

}



// every time it is clicked, add to node -- if it's not already created, create and insert into respective place in dynamic array
// else, just increment the people


// message queue and increment for second floor
// displays how many people leave (because that data was entered from the queue
void GoingDownDialog::on_pushButton_2_clicked()
{
    string s;

    if (open_door)
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        selected_floor = second + 1;
        s = selected_floor_message(selected_floor);
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    else
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        s = "Error. Must 'Open' Door before selecting\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }


    if (stackDown->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor > selected_floor && open_door && array_total() + stackDown->total_people() < MAX_CAPACITY)
    {
        stackDown->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is higher than the current one, wait
    else if (selected_floor > current_floor && open_door && stackDown->total_people() + array_total() < MAX_CAPACITY)
    {
        a[selected_floor - 1] += 1;
        stringstream ss;
        string s;

        ss << a[selected_floor - 1] << " people will later go to Floor #" << selected_floor << endl << endl;
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }

    if (open_door && array_total() + stackDown->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}


// third floor
void GoingDownDialog::on_pushButton_3_clicked()
{
    string s;

    if (open_door)
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        selected_floor = third + 1;
        s = selected_floor_message(selected_floor);
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    else
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        s = "Error. Must 'Open' Door before selecting\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }


    if (stackDown->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor > selected_floor && open_door && array_total() + stackDown->total_people() < MAX_CAPACITY)
    {
        stackDown->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is higher than the current one, wait
    else if (selected_floor > current_floor && open_door && stackDown->total_people() + array_total() < MAX_CAPACITY)
    {
        a[selected_floor - 1] += 1;
        stringstream ss;
        string s;

        ss << a[selected_floor - 1] << " people will later go to Floor #" << selected_floor << endl << endl;
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }

    if (open_door && array_total() + stackDown->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}






void GoingDownDialog::on_pushButton_4_clicked()
{
    string s;

    if (open_door)
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        selected_floor = fourth + 1;
        s = selected_floor_message(selected_floor);
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    else
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        s = "Error. Must 'Open' Door before selecting\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }


    if (stackDown->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor > selected_floor && open_door && array_total() + stackDown->total_people() < MAX_CAPACITY)
    {
        stackDown->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is higher than the current one, wait
    else if (selected_floor > current_floor && open_door && stackDown->total_people() + array_total() < MAX_CAPACITY)
    {
        a[selected_floor - 1] += 1;
        stringstream ss;
        string s;

        ss << a[selected_floor - 1] << " people will later go to Floor #" << selected_floor << endl << endl;
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }

    if (open_door && array_total() + stackDown->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}



void GoingDownDialog::on_pushButton_5_clicked()
{
    string s;

    if (open_door)
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        selected_floor = fifth + 1;
        s = selected_floor_message(selected_floor);
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    else
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        s = "Error. Must 'Open' Door before selecting\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }


    if (stackDown->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor > selected_floor && open_door && array_total() + stackDown->total_people() < MAX_CAPACITY)
    {
        stackDown->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is higher than the current one, wait
    else if (selected_floor > current_floor && open_door && stackDown->total_people() + array_total() < MAX_CAPACITY)
    {
        a[selected_floor - 1] += 1;
        stringstream ss;
        string s;

        ss << a[selected_floor - 1] << " people will later go to Floor #" << selected_floor << endl << endl;
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }

    if (open_door && array_total() + stackDown->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}

void GoingDownDialog::on_pushButton_6_clicked()
{
    string s;

    if (open_door)
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        selected_floor = sixth + 1;
        s = selected_floor_message(selected_floor);
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    else
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        s = "Error. Must 'Open' Door before selecting\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }


    if (stackDown->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor > selected_floor && open_door && array_total() + stackDown->total_people() < MAX_CAPACITY)
    {
        stackDown->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is higher than the current one, wait
    else if (selected_floor > current_floor && open_door && stackDown->total_people() + array_total() < MAX_CAPACITY)
    {
        a[selected_floor - 1] += 1;
        stringstream ss;
        string s;

        ss << a[selected_floor - 1] << " people will later go to Floor #" << selected_floor << endl << endl;
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }

    if (open_door && array_total() + stackDown->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}


void GoingDownDialog::on_pushButton_7_clicked()
{
    string s;

    if (open_door)
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        selected_floor = seventh + 1;
        s = selected_floor_message(selected_floor);
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    else
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        s = "Error. Must 'Open' Door before selecting\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }


    if (stackDown->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor > selected_floor && open_door && array_total() + stackDown->total_people() < MAX_CAPACITY)
    {
        stackDown->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is higher than the current one, wait
    else if (selected_floor > current_floor && open_door && stackDown->total_people() + array_total() < MAX_CAPACITY)
    {
        a[selected_floor - 1] += 1;
        stringstream ss;
        string s;

        ss << a[selected_floor - 1] << " people will later go to Floor #" << selected_floor << endl << endl;
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }

    if (open_door && array_total() + stackDown->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}


void GoingDownDialog::on_pushButton_8_clicked()
{
    string s;

    if (open_door)
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        selected_floor = eighth + 1;
        s = selected_floor_message(selected_floor);
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    else
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        s = "Error. Must 'Open' Door before selecting\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }


    if (stackDown->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor > selected_floor && open_door && array_total() + stackDown->total_people() < MAX_CAPACITY)
    {
        stackDown->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is higher than the current one, wait
    else if (selected_floor > current_floor && open_door && stackDown->total_people() + array_total() < MAX_CAPACITY)
    {
        a[selected_floor - 1] += 1;
        stringstream ss;
        string s;

        ss << a[selected_floor - 1] << " people will later go to Floor #" << selected_floor << endl << endl;
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }

    if (open_door && array_total() + stackDown->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}


void GoingDownDialog::on_pushButton_9_clicked()
{
    string s;

    if (open_door)
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        selected_floor = ninth + 1;
        s = selected_floor_message(selected_floor);
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    else
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        s = "Error. Must 'Open' Door before selecting\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }


    if (stackDown->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor > selected_floor && open_door && array_total() + stackDown->total_people() < MAX_CAPACITY)
    {
        stackDown->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is higher than the current one, wait
    else if (selected_floor > current_floor && open_door && stackDown->total_people() + array_total() < MAX_CAPACITY)
    {
        a[selected_floor - 1] += 1;
        stringstream ss;
        string s;

        ss << a[selected_floor - 1] << " people will later go to Floor #" << selected_floor << endl << endl;
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }

    if (open_door && array_total() + stackDown->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }

}

void GoingDownDialog::on_pushButton_10_clicked()
{
    selected_floor = tenth + 1;
    // if they pick that floor, it tells them they are at their destination, otherwise, pick another floor
    if (current_floor == selected_floor)
    {

        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if they select the floor and it's already above them, if the door is open, and isn't at max capacity
    else if (current_floor < selected_floor && open_door && array_total() + stackDown->total_people() < MAX_CAPACITY)
    {
        a[selected_floor - 1] += 1;
        stringstream ss;
        string s;

        ss << a[selected_floor - 1] << " people will later go to Floor #" << selected_floor << endl << endl;
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }

//     if it's open door and at max capacity, print a message
    if (open_door && array_total() + stackDown->total_people() == MAX_CAPACITY)
    {
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }


}



// close button
// when there is a delay -- i.e. 5 seconds, then close door automatically
void GoingDownDialog::on_pushButton_11_clicked()
{
        open_door = false;

        ui->plainTextEdit->clear();
        stringstream ss;
        string s;

        // print total people still in elevator


//        qDebug() << "stackDown->total_people() = " << stackDown->total_people() << endl;
//        qDebug() << "array_total() = " << array_total()<< endl;
        if (stackDown->total_people() + array_total() == 1)
        {
            s = "1 person in the elevator\n\n";
        }
        else
        {
            ss << stackDown->total_people() + array_total() << " total people in elevator\n\n";
            s = ss.str();

            ss.clear();
            ss.str(string());
        }

        QString qs = QString::fromStdString(s);
        ui->plainTextEdit->insertPlainText(qs);

        ss.clear();//clear any bits set
        ss.str(string());


        delay();

        ui->plainTextEdit->clear();

        // closing door before moving elevator
        s = "Closing door\n";
        qs = QString::fromStdString(s);

        ui->plainTextEdit->insertPlainText(qs);

        // if it's empty, elevator stays put
        if (stackDown->total_people() + array_total() == 0 && !open_door)
        {
            delay();
            ui->plainTextEdit->clear();
            s = "Empty elevator\n";
            qs = QString::fromStdString(s);

            ui->plainTextEdit->insertPlainText(qs);
            delay();

            this->close();
            exit(5);
//            return;
        }


        // if queue is empty but array has people in it, call the down elevator
        else if (stackDown->total_people() == 0 && array_total() > 0)
        {


            goingupdialog = new GoingUpDialog(this);


            goingupdialog->show();

            goingupdialog->array_read(a, current_floor);

            goingupdialog->exec();


            delete [] a;

            a = NULL;


            this->hide();
            this->close();
        }


        // proceeding down the elevator
        delay();
        ui->plainTextEdit->clear();


        ss << "Elevator moving" << endl << endl;
        s = ss.str();

        ss.clear();
        ss.str(string());

        qs = QString::fromStdString(s);

        ui->plainTextEdit->insertPlainText(qs);

        // incrementing floor to go to
        current_floor--;

        // display going up to _ floor -- if it's empty, delete
        while (stackDown->get_people(current_floor) == 0 && !open_door)
        {
            delay();
            ui->plainTextEdit->clear();
            ss << "Passing by Floor #" << current_floor << endl;
            s = ss.str();

            ss.clear();
            ss.str(string());

            qs = QString::fromStdString(s);
            ui->plainTextEdit->insertPlainText(qs);

            // pop()

            current_floor--;
            stackDown->pop();

        }



        delay();
        ui->plainTextEdit->clear();
        ss << "Currently on Floor #" << current_floor << endl << endl;
        s = ss.str();

        ss.clear();
        ss.str(string());

        qs = QString::fromStdString(s);
        ui->plainTextEdit->insertPlainText(qs);

        if (stackDown->get_people(current_floor) == 1)
        {
            ss << stackDown->get_people(current_floor) << " person left the elevator\n\n";
        }
        else
        {
            ss << stackDown->get_people(current_floor) << " people leave the elevator\n\n";
        }

        s = ss.str();
        ss.clear();
        ss.str(string());
        qs = QString::fromStdString(s);

        delay();
        ui->plainTextEdit->insertPlainText(qs);

        stackDown->pop();
//        current_floor--;





        delay();
        ui->plainTextEdit->clear();


        // total people still in elevator
        if (stackDown->total_people() + array_total() == 1)
        {
            s = "1 person in the elevator\n\n";
        }
        else
        {
            ss << stackDown->total_people() + array_total() << " total people in elevator\n\n";
            s = ss.str();

            ss.clear();
            ss.str(string());
        }

        qs = QString::fromStdString(s);
        ui->plainTextEdit->insertPlainText(qs);



        delay();

        s = "Click 'Close Door' to continue\n";
        qs = QString::fromStdString(s);
        ui->plainTextEdit->insertPlainText(qs);

        if (!open_door)
        {
            timer = new QElapsedTimer;
            timer->start();

            while (timer->elapsed() < 2 * 1000 && !open_door)
            {

            }


            on_pushButton_11_clicked();
        }

}



// open button
// should pause the elevator
void GoingDownDialog::on_pushButton_12_clicked()
{
    open_door = true;
}





void GoingDownDialog::array_constructor()
{
    a = new int[MAX_FLOORS];

    for (int i = 0; i < MAX_FLOORS; i++)
    {
        a[i] = 0;
    }
}

int GoingDownDialog::array_total()
{
    int count = 0;

    for (int i = 0; i < MAX_FLOORS; i++)
    {
        count += a[i];
    }

    return count;
}

void GoingDownDialog::array_delete()
{
    delete [] a;

    a = NULL;
}



// reads an array from an outside class assigns the amount to the floors
void GoingDownDialog::array_read(int s[], int f)
{
    // no 10th floor
    for (int i = 0; i < MAX_FLOORS - 1; i++)
    {
        if (s[i] > 0)
        {
            stackDown->add_people(i + 1, s[i]);
//            qDebug() << "stackDown->add_people(" << i + 1 << ", " << s[i] << endl;
        }
    }

    current_floor = f;
//    current_floor = f + 1; // program needs to start above the current floor
    int delete_floors = MAX_FLOORS - f; // after we get the highest floor, we pop off what we don't need

    for (int i = 0; i < delete_floors; i++)
    {
//        qDebug() << " popped = " << i + 1 << endl;

        stackDown->pop();
    }

    delete [] s;
    s = NULL;

    on_pushButton_11_clicked();
}




