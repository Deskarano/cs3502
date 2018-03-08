//
// Created by Othmane on 2/25/18.
//

#include "dispatcher.h"

using namespace std;

static pcb* next_job = nullptr;

void dispatcher::init(pcb* cpu_pcb, shortterm short_term) {
    dispatcher::short_term = short_term;
    dispatcher::cpu_pcb = cpu_pcb;
}

//Method encompasses all dispatcher function, to be used in driver
void dispatcher::dispatch() {
    next_job = get_next_job(short_term);
    set_pcb_data(cpu_pcb, next_job);
}

//Getting next job to be executed from the short term scheduler
pcb* dispatcher::get_next_job(shortterm st_scheduler) {
    next_job = st_scheduler.get_next_process();
    return next_job;
}

//Setting the CPU PCB to the extracted data from the selected process
void dispatcher::set_pcb_data(pcb *cpu_pcb, pcb *next_job) {
    cpu_pcb->set_ID(next_job->get_ID());
    cpu_pcb->set_base_disk_address(next_job->get_base_disk_address());
    cpu_pcb->set_base_ram_address(next_job->get_base_ram_address());
    cpu_pcb->set_state(next_job->get_state());
    cpu_pcb->set_pc(next_job->get_pc());
    cpu_pcb->set_priority(next_job->get_priority());
    cpu_pcb->set_code_size(next_job->get_code_size());
}
