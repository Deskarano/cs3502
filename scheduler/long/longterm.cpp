#include <iostream>

#include "longterm.h"
#include "../../ram/ram.h"
#include "../../disk/disk.h"

void longterm::longterm()
{

}

void longterm::load_to_ram()
{
    address = 0;

    //make sure there is room in ram and disk isn't empty
    while(!ram::is_full() && !disk::is_empty())
    {
        auto value = disk::read_word(address);
        ram::write_word(address,value);
        address += 8;
    }
}
