#ifndef CS3502_PAGE_MANAGER_H
#define CS3502_PAGE_MANAGER_H

#include <thread>

#include "../pcb/page_table/page_table.h"

#include "../pcb/pcb.h"
#include "../pcb/pcb_node.h"


struct page_manager
{
public:
    static void init();

    static int write_word(pcb *pcb, unsigned int addr, char *val);
    static int read_word(pcb *pcb, unsigned int addr, char *target);

    static void init_frames(pcb *pcb);
    static void receive_pcb(pcb *pcb, unsigned int log_addr);

    static void release_frames(pcb *pcb);

private:
    static void load_and_update(pcb *pcb, unsigned int log_addr);
    static bool *free_frames;

    static void process_work();

    static std::thread *work_thread;
    static pcb_node *work_head;
    static pcb_node *work_tail;
};


#endif //CS3502_PAGE_MANAGER_H
