//Display 13.23    implementation of the Queue Class (part 1 of 3)
//This is the implementation file queue.cpp.
//This is the implementation of the class Queue.
//The interface for the class Queue is in the header file
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include "queue.h"
#include <sstream>
using namespace std;

namespace queue
{
    //Uses cstddef:
    Queue::Queue()
    {
        front = NULL;
        back = NULL;
    }


    Queue::~Queue()
    {
        QueueNodePtr temp1, temp2;

        temp1 = front;

        while (temp1 != NULL)
        {
            temp2 = temp1->link;
            delete temp1;
            temp1 = temp2;
        }

    }

    //Uses cstddef:
//    bool Queue::empty() const
//    {
//        if (back == NULL)
//        {
//            return true;
//        }

//        return front == NULL;

//    }

    //Uses cstddef:
    void Queue::add_node(int f, int p)
    {
        if (front == NULL)
        {
            front = new QueueNode;

            front->floor = f;
            front->people = p;
            front->link = NULL; // it's both the head and tail at first

            back = front;
        }

        else
        {
            // adding something to the back of the line/queue
            QueueNodePtr temp_ptr;

            temp_ptr = new QueueNode;
            temp_ptr->floor = f;
            temp_ptr->people = p;
            temp_ptr->link = NULL; // means it's the last one

            back->link = temp_ptr; // previous tail now points to current tail
            back = temp_ptr; // previous tail becomes the created tail
        }
    }

    //Uses cstdlib and iostream:
    void Queue::remove()
    {
        if (front == NULL)
        {
            cout << "Error: Removing an item from an empty queue.\n";
//            exit(1);
        }
        else
        {
            QueueNodePtr discard;
            discard = front;

            // moving forward
            front = front->link;

            if (front == NULL) //if you removed the last node
            {
                back = NULL;
            }

            delete discard;
        }
    }

    // adds people every time they press the button
    void Queue::add_people(int f, int p)
    {
        QueueNodePtr temp = front;

        while (temp != NULL)
        {
            if (temp->floor == f)
            {
                temp->people += p;
                break;
            }
            temp = temp->link;
        }
    }

    // returns the number of people on that floor
    int Queue::get_people(int f)
    {
        QueueNodePtr temp = front;

        while (temp != NULL)
        {
            if (temp->floor == f)
            {
                return temp->people;
            }
            temp = temp->link;
        }

        return 0;
    }



    // returns how many people are leaving that floor
    string Queue::print_node()
    {
        if (front != NULL)
        {
            stringstream ss;
            ss << "floor = " << front->floor << "   people = " << front->people;
            string s = ss.str();
            return s;
        }

        return 0;
    }

    // returns the total people on the elevator
    int Queue::total_people()
    {
        QueueNodePtr here = front;
        int peopleCount = 0;

        while (here != NULL)
        {
            peopleCount += here->people;
            here = here->link;
        }

        return peopleCount;
    }



}//queue
