//
// Created by Othmane on 2/13/18.
//

#ifndef CS3502_DISK_H
#define CS3502_DISK_H

struct disk {

public:
    static void init(unsigned int num_bytes);
    static void write_word(unsigned int addr, int val);
    static int read_word(unsigned int addr);
    static void clear_disk();
    static bool is_full();

private:
    //Variables
    static unsigned int num_bytes;
    static unsigned char *data;
    static unsigned int used_memory;
    //Methods
    static void write_byte(unsigned int addr, unsigned char val);
    static unsigned char read_byte(unsigned int addr);

};

#endif //CS3502_DISK_H
