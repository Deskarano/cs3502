#ifndef CS3502_LOCK_H
#define CS3502_LOCK_H

#include <mutex>
#include <condition_variable>

class lock
{
public:
    lock();

    void notify();
    void wait();
    bool try_wait();

private:
    std::mutex mutex;
    std::condition_variable condition;
    unsigned int count;
};

#endif //CS3502_LOCK_H