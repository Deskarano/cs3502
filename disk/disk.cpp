//
// Created by Othmane on 2/13/18.
//

#include "disk.h"
#include <iostream>

unsigned int disk::num_bytes = 0;
unsigned char *disk::data = nullptr;
unsigned int disk::used_memory = 0;

void disk::init(unsigned int num_bytes) {

    disk::num_bytes = num_bytes;
    disk::data = new unsigned char[num_bytes];

}

void disk::write_byte(unsigned int addr, unsigned char val) {

    if(addr < num_bytes) {
        data[addr] = val;
        used_memory ++;
    }
    else {
        std::cout << "--disk-error (write_byte): address " << std::hex << addr << " is out of range\n";
    }

}

unsigned char disk::read_byte(unsigned int addr) {

    if(addr < num_bytes) {
        return data[addr];
    }
    else {
        std::cout << "--disk-error (read_byte): address " << std::hex << addr << " is out of range\n";
        return 0;
    }

}

void disk::write_word(unsigned int addr, int val) {

    auto val1 = (unsigned char) ((val >> 24) & 0b11111111);
    auto val2 = (unsigned char) ((val >> 16) & 0b11111111);
    auto val3 = (unsigned char) ((val >> 8) & 0b11111111);
    auto val4 = (unsigned char) (val & 0b11111111);

    write_byte(addr, val1);
    write_byte(addr + 1, val2);
    write_byte(addr + 2, val3);
    write_byte(addr + 3, val4);

}

int disk::read_word(unsigned int addr) {

    int val1 = read_byte(addr);
    int val2 = read_byte(addr + 1);
    int val3 = read_byte(addr + 2);
    int val4 = read_byte(addr + 3);

    return (val1 << 24) + (val2 << 16) + (val3 << 8) + val4;

}

void disk::clear_disk() {

    for (int i = 0; i < num_bytes; ++i)
        data[i] = '\0';
    used_memory = 0;

}

bool disk::is_full(){

    return used_memory >= num_bytes;

}

