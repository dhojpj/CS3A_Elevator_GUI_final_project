//This is the header file queue.h. This is the interface for the class Queue,
//which is a class for a queue of symbols.
#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
using namespace std;

namespace queue
{
    struct QueueNode
    {
        int floor;
        int people;
        QueueNode* link;
    };

    typedef QueueNode* QueueNodePtr;

    class Queue
    {

    public:

        Queue(); //Initializes the object to an empty queue.
//        Queue(const Queue& aQueue);
        ~Queue();
        void add_node(int f, int p);
        void add_people(int f, int p);  // adds people depending on the number of people pressing the button
        int get_people(int f);    // returns the number of people on that floor
        string print_node();
        void remove(); //Precondition: The queue is not empty. //Returns the item at the front of the queue
//        bool empty() const;  //Returns TRUE if the queue is empty. Returns FALSE otherwise.
        int total_people();

    private:
//        QueueNodePtr front, back; //Points to the head of a linked list.  //Items are removed at the head
        QueueNodePtr front, back; //Points to the node at the other end of the linked list. Items are added at this end.
    };
}//queue
#endif //QUEUE_H
