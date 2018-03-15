#ifndef CS3502_DISK_H
#define CS3502_DISK_H

struct disk
{
public:
    static void init(unsigned int num_words);

    static void write_word(unsigned int addr, const char val[8]);
    static char *read_word(unsigned int addr);

    static unsigned int size()
    { return num_words; }

private:
    static unsigned int num_words;
    static char *data;
};

#endif //CS3502_DISK_H
