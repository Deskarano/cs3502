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

template <class T>
queue<T>::queue()
{
    length = 0;
}

template <class T>
void queue<T>::push(T *element)
{
    queue_node<T> *new_node = new queue_node<T>(element);

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
T *queue<T>::pop()
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

template <class T>
T *queue<T>::as_array()
{
    auto ret = new T[length];
    unsigned int index = 0;

    auto current = (queue_node<T> *) head;
    while(current->next != nullptr)
    {
        ret[index] = current->element;

        index++;
        current = current->next;
    }

    ret[index] = current->element;
    return ret;
}