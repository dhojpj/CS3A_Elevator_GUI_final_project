//This is the header file stack.h. This is the interface for the class Stack,
//which is a class for a stack of symbols.
#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

namespace stack
{
    struct StackNode
    {
        int floor;
        int people;
        StackNode* link;
    };

    typedef StackNode* StackNodePtr;

    class Stack
    {
    public:
        Stack();     //Initializes the object to an empty stack.
        ~Stack();     //Destroys the stack and returns all the memory to the freestore.

        void push(int f, int p);     //Postcondition: the_symbol has been added to the stack.
        void pop();     //Precondition: The stack is not empty.        //Returns the top symbol on the stack and removes that    //top symbol from the stack.
        bool empty() const;     //Returns TRUE if the stack is empty. Returns FALSE otherwise.

        int get_people(int f);
        int total_people();
        void add_people(int f, int p);

    private:
        StackNodePtr top;
    };
}//stack
#endif //STACK_H
