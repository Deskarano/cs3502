#include <iostream>
#include "page_manager.h"

#include "ram/ram.h"
#include "../log/log_status.h"

#include "../utils/memcpy.h"
#include "../utils/lock.h"
#include "../sched/short/shortterm.h"

bool *page_manager::free_frames = nullptr;

pcb_node *page_manager::work_head = nullptr;
pcb_node *page_manager::work_tail = nullptr;

static lock *recv_lock = new lock;

void page_manager::init()
{
    free_frames = new bool[(ram::size() / 4) + 1];
    for(int i = 0; i < (ram::size() / 4) + 1; i++)
    {
        free_frames[i] = true;
    }

    work_head = nullptr;
    work_tail = nullptr;

    log_status::log_pager_init();
}

int page_manager::write_word(page_table *table, unsigned int addr, char *val)
{
    unsigned int phys_addr = table->lookup_page(addr);

    log_status::log_pager_lookup(table->pcb_id, addr, phys_addr);

    if(phys_addr == PAGE_FAULT)
    {
        return PAGE_FAULT;
    }

    ram::write_word(phys_addr, val);
    return 0;
}

int page_manager::read_word(page_table *table, unsigned int addr, char *target)
{
    unsigned int phys_addr = table->lookup_page(addr);

    log_status::log_pager_lookup(table->pcb_id, addr, phys_addr);

    if(phys_addr == PAGE_FAULT)
    {
        return PAGE_FAULT;
    }

    char *val = ram::read_word(phys_addr);
    for(int i = 0; i < 8; i++)
    {
        target[i] = val[i];
    }

    delete val;
    return 0;
}

void page_manager::init_frames(page_table *table)
{
    log_status::log_pager_init_frames(table->pcb_id);
}

void page_manager::process_work()
{
    while(work_head != nullptr)
    {
        load_and_update(work_head->value->table, work_head->misc);
        work_head->value->state = PCB_READY;
        shortterm::receive_pcb(work_head->value);

        pcb_node *del = work_head;
        work_head = work_head->next;

        delete del;
    }
}

void page_manager::receive_pcb(pcb *pcb, unsigned int log_addr)
{
    recv_lock->wait();

    log_status::log_pager_receive_pcb(pcb->ID, log_addr);

    pcb_node *node = new pcb_node(pcb);
    node->misc = log_addr;

    if(work_head == nullptr)
    {
        work_head = node;
        work_tail = node;

        new std::thread(&page_manager::process_work);
    }
    else
    {
        work_tail->next = node;
        work_tail = node;
    }

    recv_lock->notify();
}

void page_manager::load_and_update(page_table *table, unsigned int log_addr)
{
    unsigned int page_num = (table->base_disk_address + log_addr) / 16;
    unsigned int frame_num = 0xFFFFFFFF;

    //find the first free frame
    for(unsigned int i = 0; i < ram::size() / 4; i++)
    {
        if(free_frames[i])
        {
            frame_num = i;

            break;
        }
    }

    if(frame_num == 0xFFFFFFFF)
    {
        unsigned int old_log_addr = table->least_used_frame();
        frame_num = table->lookup_page(old_log_addr) / 16;

        release_frame(table, old_log_addr);
        table->invalidate_page(old_log_addr);
    }

    log_status::log_pager_load_update(table->pcb_id, log_addr / 16 * 16, 16 * frame_num);

    free_frames[frame_num] = false;

    disk_to_ram(16 * page_num, 16 * frame_num, 4);
    table->add_page(log_addr / 16, frame_num);
}

void page_manager::release_frame(page_table *table, unsigned int log_addr)
{
    unsigned int phys_addr = table->lookup_page(log_addr);

    log_status::log_pager_release_frame(table->pcb_id, log_addr, phys_addr);

    ram_to_disk(phys_addr, table->base_disk_address + log_addr, 4);
    free_frames[phys_addr / 16] = true;
}

void page_manager::release_all_frames(page_table *table)
{
    log_status::log_pager_release_all_frames(table->pcb_id);

    for(unsigned int i = 0; i < table->num_frames; i++)
    {
        unsigned int phys_addr = table->lookup_page(16 * i);
        if(phys_addr != PAGE_FAULT)
        {
            release_frame(table, 16 * i);
        }
    }
}