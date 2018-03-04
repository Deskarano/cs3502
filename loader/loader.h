//
// Created by zachs on 3/4/2018.
//

#ifndef CS3502_MASTER_LOADER_H
#define CS3502_MASTER_LOADER_H

#include <fstream>

class Loader
{
public:
    Loader();
    ~Loader();
    void loadProgram(std::ifstream program);
};

#endif //CS3502_MASTER_LOADER_H
