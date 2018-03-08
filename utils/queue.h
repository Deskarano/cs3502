#ifndef CS3502_QUEUE_H
#define CS3502_QUEUE_H

template <class T>
class queue
{
public:
    queue();

    void push(T *element);
    T *pop();

    T *as_array();

private:
    void *head;
    unsigned int length;
};


#endif //CS3502_QUEUE_H
