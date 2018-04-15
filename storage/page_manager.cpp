#include <iostream>
#include "page_manager.h"

#include "ram/ram.h"
#include "../log/log_status.h"

#include "../utils/memcpy.h"
#include "../utils/lock.h"
#include "../sched/short/shortterm.h"

bool *page_manager::free_frames = nullptr;

std::thread *page_manager::work_thread = nullptr;
pcb_node *page_manager::work_head = nullptr;
pcb_node *page_manager::work_tail = nullptr;

static lock *receive_lock = new lock;

void page_manager::init()
{
    free_frames = new bool[(ram::size() / 4) + 1];
    for(int i = 0; i < (ram::size() / 4) + 1; i++)
    {
        free_frames[i] = true;
    }

    work_thread = nullptr;
    work_head = nullptr;

    log_status::log_pager_init();
}

int page_manager::write_word(pcb *pcb, unsigned int addr, char *val)
{
    unsigned int phys_addr = pcb->table->lookup_page(addr);

    log_status::log_pager_lookup(pcb->ID, addr, phys_addr);

    if(phys_addr == PAGE_FAULT)
    {
        return PAGE_FAULT;
    }

    ram::write_word(phys_addr, val);
    return 0;
}

int page_manager::read_word(pcb *pcb, unsigned int addr, char *target)
{
    unsigned int phys_addr = pcb->table->lookup_page(addr);

    log_status::log_pager_lookup(pcb->ID, addr, phys_addr);

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

void page_manager::init_frames(pcb *pcb)
{
    log_status::log_pager_init_frames(pcb->ID);

    //one of each type of frame
    load_and_update(pcb, 0);
    load_and_update(pcb, 4 * pcb->code_size);
    load_and_update(pcb, 4 * (pcb->code_size + pcb->input_size));
    load_and_update(pcb, 4 * (pcb->code_size + pcb->input_size + pcb->output_size));
}

void page_manager::process_work()
{
    while(work_head != nullptr)
    {
        load_and_update(work_head->value, work_head->misc);
        work_head->value->state = PCB_READY;
        shortterm::receive_pcb(work_head->value);

        pcb_node *del = work_head;
        work_head = work_head->next;

        delete del;
    }
}

void page_manager::receive_pcb(pcb *pcb, unsigned int log_addr)
{
    receive_lock->wait();

    log_status::log_pager_receive_pcb(pcb->ID, log_addr);

    pcb_node *node = new pcb_node(pcb);
    node->misc = log_addr;

    if(work_head == nullptr)
    {
        work_head = node;
        work_tail = node;

        work_thread = new std::thread(&page_manager::process_work);
    }
    else
    {
        work_tail->next = node;
        work_tail = node;
    }

    receive_lock->notify();
}

void page_manager::load_and_update(pcb *pcb, unsigned int log_addr)
{
    unsigned int page_num = (pcb->base_disk_address + log_addr) / 16;
    unsigned int frame_num = 0;

    //find the first free frame
    for(unsigned int i = 0; i < ram::size() / 4; i++)
    {
        if(free_frames[i])
        {
            frame_num = i;
            free_frames[i] = false;
            break;
        }

        if(i == ram::size() / 4 - 1)
        {
            std::cout << "ERROR: NO FRAMES LEFT\n";
            exit(24601);
        }
        //TODO: add logic for no free frames
    }

    log_status::log_pager_load_update(pcb->ID, log_addr / 16 * 16, 16 * frame_num);

    disk_to_ram(16 * page_num, 16 * frame_num, 4);
    pcb->table->add_page(log_addr / 16, frame_num);
}

void page_manager::release_frames(pcb *pcb)
{
    log_status::log_pager_release_frames(pcb->ID);

    for(unsigned int i = 0; i < pcb->get_total_size(); i += 4)
    {
        unsigned int log_addr = pcb->table->lookup_page(4 * i);
        if(log_addr != PAGE_FAULT)
        {
            ram_to_disk(log_addr, pcb->base_disk_address + 4 * i, 4);
            free_frames[log_addr / 16] = true;
        }
    }
}