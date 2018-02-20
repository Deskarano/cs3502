//
// Created by Othmane on 2/13/18.
//

#ifndef CS3502_DISK_H
#define CS3502_DISK_H

struct disk {

public:
    static void init(unsigned int num_words);

    static void write_word(unsigned int addr, const char val[8]);
    static char *read_word(unsigned int addr);

    static void clear_disk();
    static bool is_full();

private:
    //Variables
    static unsigned int num_words;
    static char *data;

    static unsigned int used_memory;
};

#endif //CS3502_DISK_H
