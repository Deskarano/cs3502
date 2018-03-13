#include "lock.h"

#include <iostream>

lock::lock()
{
    count = 1;
}

void lock::notify()
{
    std::unique_lock<decltype(mutex)> lock(mutex);
    ++count;
    condition.notify_one();
}

void lock::wait()
{
    std::unique_lock<decltype(mutex)> lock(mutex);
    while(!count) condition.wait(lock);

    --count;
}

bool lock::try_wait()
{
    std::unique_lock<decltype(mutex)> lock(mutex);
    if(count)
    {
        --count;
        return true;
    }

    return false;
}