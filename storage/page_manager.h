#ifndef CS3502_PAGE_MANAGER_H
#define CS3502_PAGE_MANAGER_H

#include "../pcb/page_table/page_table.h"

#include "../pcb/pcb.h"
#include "../pcb/pcb_node.h"


struct page_manager
{
public:
    static void init();

    static int write_word(page_table *table, unsigned int addr, char *val);
    static int read_word(page_table *table, unsigned int log_addr, char *target);

    static void init_frames(page_table *table);
    static void receive_pcb(pcb *pcb, unsigned int log_addr);

    static unsigned int release_frame(page_table *table, unsigned int phys_addr);
    static void release_all_frames(page_table *table);

private:
    static void load_and_update(page_table *table, unsigned int log_addr);
    static void process_work();

    static bool *free_frames;

    static pcb_node *work_head;
    static pcb_node *work_tail;
};


#endif //CS3502_PAGE_MANAGER_H
