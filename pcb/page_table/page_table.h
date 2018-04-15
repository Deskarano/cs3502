#ifndef CS3502_PAGE_TABLE_H
#define CS3502_PAGE_TABLE_H

#define PAGE_FAULT 0xFFFFFFFF

class page_table
{
public:
    page_table(unsigned int num_words);
    ~page_table();

    void add_page(unsigned int frame_num, unsigned int page_num);
    unsigned int lookup_page(unsigned int logical_address);

private:
    unsigned int *entries;
    bool *valid;
};


#endif //CS3502_PAGE_TABLE_H
