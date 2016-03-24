#include "goingupdialog.h"
#include "ui_goingupdialog.h"
#include <QPalette>
#include "windows.h"
#include <sstream>
#include <QString>
#include <QTime>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QDebug>
#include "goingdowndialog.h"
using namespace queue;



// constructor
GoingUpDialog::GoingUpDialog(QWidget *parent) : QDialog(parent), ui(new Ui::GoingUpDialog)
{

    // this is another window class, this time green
    QPalette pal = this->palette();
    pal.setColor(this->backgroundRole(), Qt::green);
    this->setPalette(pal);

    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);


    // creating Queue memory on the heap
    queueUp = new Queue;


    // generates a linked list queue of floors, with 0 people each
    // people will increment later -- once inside the elevator they can press floor buttons
    for (int i = 2; i <= 10; i++)
    {
        queueUp->add_node(i, 0);
    }


    // calling the dynamic array
    array_constructor();


}


// include a constructor that calls the original constructor but from a certain starting point


// destructor
GoingUpDialog::~GoingUpDialog()
{
//    delete [] a;
//    a = NULL;
//    delete queueUp;
//    queueUp = NULL;
    delete ui;
}



// multi selection increments manually for their respective nodes and tallies total
void GoingUpDialog::set_current_floor(int f)
{
    current_floor = f;

    stringstream ss;
    ss << "Floor #" << current_floor << endl;
    string s = ss.str();

    ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable


}



// function that delays time -- better than using Sleep which only freezes the application
void GoingUpDialog::delay()
{
    QTime dieTime = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


// returns a string for the button selections
string GoingUpDialog::selected_floor_message(int f)
{
    stringstream ss;

    ss << "Floor #" << f << " was selected" << endl;

    return ss.str();
}

// returns a string for the button selections
string GoingUpDialog::total_people_to_floor_message(int f)
{
    stringstream ss;

    if (queueUp->get_people(f) == 1)
    {
        ss << queueUp->get_people(f) << " person going to Floor #" << f << endl;
    }
    else
    {
        ss << queueUp->get_people(f) << " people going to Floor #" << f << endl;
    }

    return ss.str();
}

// returns message of what floor they're on/passing by
string GoingUpDialog::current_floor_message(int f)
{
    stringstream ss;

    ss << "Elevator is currently at Floor #" << f << endl;

    return ss.str();
}





// first floor button -- save the number of people who want to go down (when current_floor > 1)
void GoingUpDialog::on_pushButton_clicked()
{
    selected_floor = first + 1;
    // if they pick that floor, it tells them they are at their destination, otherwise, pick another floor
    if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if they select the floor and it's already above them, if the door is open, and isn't at max capacity
    else if (current_floor > selected_floor && open_door && array_total() + queueUp->total_people() < MAX_CAPACITY)
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
    if (open_door && array_total() + queueUp->total_people() == MAX_CAPACITY)
    {
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}

// second floor
void GoingUpDialog::on_pushButton_2_clicked()
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


    if (queueUp->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor < selected_floor && open_door && array_total() + queueUp->total_people() < MAX_CAPACITY)
    {
        queueUp->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is lower than the current one, wait
    else if (selected_floor < current_floor && open_door && queueUp->total_people() + array_total() < MAX_CAPACITY)
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

    if (open_door && array_total() + queueUp->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}

// third floor
void GoingUpDialog::on_pushButton_3_clicked()
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


    if (queueUp->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor < selected_floor && open_door && array_total() + queueUp->total_people() < MAX_CAPACITY)
    {
        queueUp->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is lower than the current one, wait
    else if (selected_floor < current_floor && open_door && queueUp->total_people() + array_total() < MAX_CAPACITY)
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

    if (open_door && array_total() + queueUp->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}

// fourth floor
void GoingUpDialog::on_pushButton_4_clicked()
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


    if (queueUp->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor < selected_floor && open_door && array_total() + queueUp->total_people() < MAX_CAPACITY)
    {
        queueUp->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is lower than the current one, wait
    else if (selected_floor < current_floor && open_door && queueUp->total_people() + array_total() < MAX_CAPACITY)
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

    if (open_door && array_total() + queueUp->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}


void GoingUpDialog::on_pushButton_5_clicked()
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


    if (queueUp->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor < selected_floor && open_door && array_total() + queueUp->total_people() < MAX_CAPACITY)
    {
        queueUp->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is lower than the current one, wait
    else if (selected_floor < current_floor && open_door && queueUp->total_people() + array_total() < MAX_CAPACITY)
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

    if (open_door && array_total() + queueUp->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}

void GoingUpDialog::on_pushButton_6_clicked()
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


    if (queueUp->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor < selected_floor && open_door && array_total() + queueUp->total_people() < MAX_CAPACITY)
    {
        queueUp->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is lower than the current one, wait
    else if (selected_floor < current_floor && open_door && queueUp->total_people() + array_total() < MAX_CAPACITY)
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

    if (open_door && array_total() + queueUp->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}

void GoingUpDialog::on_pushButton_7_clicked()
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


    if (queueUp->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor < selected_floor && open_door && array_total() + queueUp->total_people() < MAX_CAPACITY)
    {
        queueUp->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is lower than the current one, wait
    else if (selected_floor < current_floor && open_door && queueUp->total_people() + array_total() < MAX_CAPACITY)
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

    if (open_door && array_total() + queueUp->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}


void GoingUpDialog::on_pushButton_8_clicked()
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


    if (queueUp->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor < selected_floor && open_door && array_total() + queueUp->total_people() < MAX_CAPACITY)
    {
        queueUp->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is lower than the current one, wait
    else if (selected_floor < current_floor && open_door && queueUp->total_people() + array_total() < MAX_CAPACITY)
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

    if (open_door && array_total() + queueUp->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}

void GoingUpDialog::on_pushButton_9_clicked()
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


    if (queueUp->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor < selected_floor && open_door && array_total() + queueUp->total_people() < MAX_CAPACITY)
    {
        queueUp->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is lower than the current one, wait
    else if (selected_floor < current_floor && open_door && queueUp->total_people() + array_total() < MAX_CAPACITY)
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

    if (open_door && array_total() + queueUp->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}

void GoingUpDialog::on_pushButton_10_clicked()
{
    string s;

    if (open_door)
    {
        // after pressing button, increment people going there by 1
        ui->plainTextEdit->clear();
        selected_floor = tenth + 1;
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


    if (queueUp->total_people() + array_total() == MAX_CAPACITY)
    {
        stringstream ss;
        ss << "Error. Max Capacity of " << MAX_CAPACITY << " people.\n";
        s = ss.str();

        ss.clear();
        ss.str(string());

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if the floor they want is higher than the current one, then let them in
    else if (current_floor < selected_floor && open_door && array_total() + queueUp->total_people() < MAX_CAPACITY)
    {
        queueUp->add_people(selected_floor, 1);

        s = total_people_to_floor_message(selected_floor);

        ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
    }
    // if it's the same one, tell them so
    else if (current_floor == selected_floor)
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText(QString::fromStdString(current_floor_message(selected_floor))); // need to save the floor onto a private variable
    }
    // if the one they select is lower than the current one, wait
    else if (selected_floor < current_floor && open_door && queueUp->total_people() + array_total() < MAX_CAPACITY)
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

    if (open_door && array_total() + queueUp->total_people() == MAX_CAPACITY)
    {
        delay();
        ui->plainTextEdit->clear();
        string s = "Elevator at Max Capacity\n\n";
        ui->plainTextEdit->insertPlainText(QString::fromStdString(s)); // need to save the floor onto a private variable
    }
}


// close button
void GoingUpDialog::on_pushButton_11_clicked()
{
    open_door = false;

    ui->plainTextEdit->clear();
    stringstream ss;
    string s;

    // total people still in elevator
    if (queueUp->total_people() + array_total() == 1)
    {
        s = "1 person in the elevator\n";
    }
    else
    {
        ss << queueUp->total_people() + array_total() << " total people in elevator\n";
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

    s = "Closing door\n";
    qs = QString::fromStdString(s);

    ui->plainTextEdit->insertPlainText(qs);


    // if it's empty, elevator stays put
    if (queueUp->total_people() + array_total() == 0 && !open_door)
    {
        delay();
        ui->plainTextEdit->clear();
        s = "Empty elevator\n";
        qs = QString::fromStdString(s);

        ui->plainTextEdit->insertPlainText(qs);
        delay();

        this->close();

        exit(6);
//        return;


//        QMessageBox::StandardButton reply;

//        reply = QMessageBox::question(this,tr("Question"),tr("Exit program?"));


//        // for the pop-up question of whether the user wants to go into elevator
//        if (reply == QMessageBox::Yes)
//        {
//            ui->plainTextEdit->clear();

//            exit(1);
//        }
//        else // go back to main window
//        {
//              this->close();
//        }
    }
    // if queue is empty but array has people in it, call the down elevator
    else if (queueUp->total_people() == 0 && array_total() > 0)
    {


        goingdowndialog = new GoingDownDialog(this);

        goingdowndialog->show();

        goingdowndialog->array_read(a, current_floor);

        goingdowndialog->exec(); // shows the new form


        delete [] a;

        a = NULL;

//        goingdowndialog->open();


        // this isn't doing what i need it to
        this->hide();
        this->close();
//        this->done(55);
//        return;

//        this->closeEve
//        this->quit();
//        array_constructor();
//        ~GoingUpDialog(this);

//        goingdowndialog->exec();



//        goingdowndialog->on_pushButton_11_clicked();

        // hide/close previous window


    }
    delay();
    ui->plainTextEdit->clear();

    // incrementing floor to go to
    current_floor++;

    ss << "Going to Floor #" << current_floor << endl << endl;
    s = ss.str();

    ss.clear();
    ss.str(string());

    qs = QString::fromStdString(s);

    ui->plainTextEdit->insertPlainText(qs);


    // display going up to _ floor -- if it's empty, delete
    while (queueUp->get_people(current_floor) == 0 && !open_door)
    {

        delay();
        ui->plainTextEdit->clear();
        ss << "Passing by Floor #" << current_floor << endl;
        s = ss.str();

        ss.clear();
        ss.str(string());

        qs = QString::fromStdString(s);
        ui->plainTextEdit->insertPlainText(qs);

        queueUp->remove();

        current_floor++;

        if (open_door)
        {
            delay();
            ui->plainTextEdit->clear();

            s = "Door opened\n\n";
            ui->plainTextEdit->insertPlainText(QString::fromStdString(s));
        }


    }



    delay();
    ui->plainTextEdit->clear();
    ss << "Currently on Floor #" << current_floor << endl << endl;
    s = ss.str();

    ss.clear();
    ss.str(string());

    qs = QString::fromStdString(s);
    ui->plainTextEdit->insertPlainText(qs);

    if (queueUp->get_people(current_floor) == 1)
    {
        ss << queueUp->get_people(current_floor) << " person left the elevator\n\n";
    }
    else
    {
        ss << queueUp->get_people(current_floor) << " people leave the elevator\n\n";
    }


    s = ss.str();
    ss.clear();
    ss.str(string());
    qs = QString::fromStdString(s);

    delay();
    ui->plainTextEdit->insertPlainText(qs);

    queueUp->remove();





    delay();
    ui->plainTextEdit->clear();



    // total people still in elevator
    if (queueUp->total_people() + array_total() == 1)
    {
        s = "1 person in the elevator\n\n";
    }
    else
    {
        ss << queueUp->total_people() + array_total() << " total people in elevator\n\n";
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
void GoingUpDialog::on_pushButton_12_clicked()
{
    open_door = true;
}





void GoingUpDialog::array_constructor()
{
    a = new int[MAX_FLOORS];

    for (int i = 0; i < MAX_FLOORS; i++)
    {
        a[i] = 0;
    }
}

int GoingUpDialog::array_total()
{
    int count = 0;

    for (int i = 0; i < MAX_FLOORS; i++)
    {
        count += a[i];
    }

    return count;
}

void GoingUpDialog::array_delete()
{
//    for (int i = 0; i < MAX_FLOORS; i++)
//    {
//        delete a[i];
//    }

    delete [] a;

    a = NULL;
}



// reads an array from an outside class assigns the amount to the floors
void GoingUpDialog::array_read(int s[], int f)
{
//    int lowest_floor = 0;

    // floors 2 to 10
    for (int i = MAX_FLOORS - 1; i > 1; i--)
    {
        if (s[i] > 0)
        {
            queueUp->add_people(i + 1, s[i]);
//            qDebug() << "floor = " << i + 1 << " poeple =  " << s[i] << endl;
//            lowest_floor = i + 1;
        }

    }

//    lowest_floor++; // because the array is -1
    current_floor = f;

    // after we get the highest floor, we pop off what we don't need
//    int delete_floors = MAX_FLOORS - highest_floor;

    for (int i = 1; i < current_floor; i++)
    {
//        qDebug() << " remove " << i << endl;
        queueUp->remove();
    }



    on_pushButton_11_clicked();
}
