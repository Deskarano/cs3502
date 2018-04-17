#ifndef CS3502_PAGE_TABLE_H
#define CS3502_PAGE_TABLE_H

#define PAGE_FAULT 0xFFFFFFFF

class page_table
{
public:
    page_table(unsigned int num_words, unsigned int base_disk_address, unsigned int pcb_id);
    ~page_table();

    void add_page(unsigned int frame_num, unsigned int page_num);
    unsigned int lookup_page(unsigned int logical_address);

    void invalidate_page(unsigned int logical_address);
    unsigned int least_used_frame();

    unsigned int num_frames;
    unsigned int pcb_id;
    unsigned int base_disk_address;

private:
    unsigned int *entries;
    bool *valid;
    int *count;
};


#endif //CS3502_PAGE_TABLE_H
