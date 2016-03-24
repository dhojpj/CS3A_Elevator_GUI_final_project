//This is the implementation file stack.cpp.
//This is the implementation of the class Stack.
//The interface for the class Stack is in the header file stack.h.
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include "stack.h"
using namespace std;



namespace stack
{
    //Uses cstddef:
    Stack::Stack() : top(NULL)
    {
    //Body intentionally empty.
    }

    Stack::~Stack()
    {
        StackNodePtr temp;
        while (!empty())
        {
            temp = top->link;

            delete top;

            top = temp;
        }
    }

    //Uses cstddef:
    bool Stack::empty() const
    {
        return (top == NULL);
    }

    void Stack::push(int f, int p)
    {
        if (top == NULL)
        {
            top = new StackNode;

            top->floor = f;
            top->people = p;
            top->link = NULL;
        }
        else
        {
            StackNodePtr head = new StackNode;

            head->floor = f;
            head->people = p;
            head->link = top;
            top = head;
        }

    }
    //Uses iostream:
    void Stack::pop()
    {
        if (empty())
        {
           exit(2);
        }

        // save the address of the data
        StackNodePtr temp_ptr = top;

        // setting it
//        temp_ptr = top;

        // changing address to next one
        top = top->link;

        // delete the old data
        delete temp_ptr;
        temp_ptr = NULL;
    }

    int Stack::get_people(int f)
    {
        StackNodePtr temp = top;

        while (temp != NULL)
        {
            if (temp->floor == f)
            {
                return temp->people;
                break;
            }

            temp = temp->link;
        }

        return 0;
    }

    int Stack::total_people()
    {
        int count = 0;
        StackNodePtr temp = top;

        while (temp != NULL)
        {
            count += temp->people;
            temp = temp->link;
        }

        return count;
    }

    void Stack::add_people(int f, int p)
    {
        StackNodePtr temp = top;

        while (temp != NULL)
        {
            if (temp->floor == f)
            {
                temp->people += p;
                break;
            }
            else
            {
                temp = temp->link;
            }
        }
    }


}//stack
