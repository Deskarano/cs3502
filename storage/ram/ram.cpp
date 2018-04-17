#include <iostream>
#include "ram.h"

#include "../../log/log_status.h"
#include "../../log/log_error.h"

#include "../../utils/lock.h"

unsigned int ram::num_words = 0;
page_frame *ram::frames = nullptr;
unsigned int *ram::frame_owners = nullptr;

static lock *ram_lock = new lock;

void ram::init(unsigned int num_words)
{
    log_status::log_ram_init(num_words);

    ram::num_words = num_words;
    frames = new page_frame[(num_words / 4) + 1];
    frame_owners = new unsigned int[(num_words / 4) + 1];
}

void ram::write_word(unsigned int addr, char val[8], unsigned int requester)
{
    unsigned int f = (2 * addr) / 32;

    if(requester == frame_owners[f] || requester == 0)
    {
        if(addr / 4 < num_words)
        {
            ram_lock->wait();

            log_status::log_ram_write_word(addr, val);

            for(int i = 0; i < 8; i++)
            {
                unsigned int d = (2 * addr) % 32 + i;

                frames[f].data[d] = val[i];
            }

            ram_lock->notify();
        }
        else
        {
            log_error::ram_write_word_range(addr);
        }
    }
    else
    {
        std::cout << "REQUESTER ERROR!!\n";
        log_status::dump_ram();
        exit(1);
    }
}

char *ram::read_word(unsigned int addr, unsigned int requester)
{
    unsigned int f = (2 * addr) / 32;

    if(requester == frame_owners[f] || requester == 0)
    {
        if(addr / 4 < num_words)
        {
            ram_lock->wait();

            auto result = new char[8];
            for(int i = 0; i < 8; i++)
            {
                unsigned int d = (2 * addr) % 32 + i;

                result[i] = frames[f].data[d];
            }

            log_status::log_ram_read_word(addr, result);

            ram_lock->notify();
            return result;
        }
        else
        {
            log_error::ram_read_word_range(addr);
        }
    }
    else
    {
        std::cout << "REQUESTER ERROR!!\n";
        log_status::dump_ram();
        exit(1);
    }
}

void ram::set_frame_owner(unsigned int addr, unsigned int owner)
{
    unsigned int f = (2 * addr) / 32;
    frame_owners[f] = owner;
}

unsigned int ram::get_frame_owner(unsigned int addr)
{
    unsigned int f = (2 * addr) / 32;
    return frame_owners[f];
}

unsigned int ram::size()
{
    return num_words;
}