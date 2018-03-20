//
// Created by guitar on 3/16/2018.
//

#ifndef CS3502_CUSTOM_CLOCK_H
#define CS3502_CUSTOM_CLOCK_H

#include <time.h>;

class custom_clock
{
public:
    custom_clock();
private:
    clockid_t my_id;
};

#endif //CS3502_CUSTOM_CLOCK_H
