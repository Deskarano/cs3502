#include "queue.h"

template <class T>
class queue_node
{
public:
    explicit queue_node(T *element)
    {
        this->element = element;
    }

    T *element;
    queue_node<T> *next;
};

void queue::queue()
{
    length = 0;
}

template <class T>
void queue::push(T *element)
{
    queue_node<T> *new_node = new queue_node(element);

    if(head == nullptr)
    {
        head = new_node;
    }
    else
    {
        auto current = (queue_node<T> *) head;
        while(current->next != nullptr)
        {
            current = current->next;
        }

        current->next = new_node;
    }

    length++;
    return;
}

template <class T>
T *queue::pop()
{
    if(head != nullptr)
    {
        auto del = (queue_node<T> *) head;
        auto ret = del->element;

        head = del->next;
        length--;

        delete del;
        return ret;
    }
};