//
// Created by Othmane on 2/25/18.
//

#ifndef CS3502_DISPATCHER_H
#define CS3502_DISPATCHER_H

#include "../pcb/pcb.h"
#include "../scheduler/short/shortterm.h"


class dispatcher {

public:
    void init(pcb* cpu_pcb, shortterm short_term);
    void dispatch();
    pcb* get_next_job(shortterm short_term);
    void set_pcb_data(pcb* cpu_pcb, pcb* next_job);

private:
    pcb* cpu_pcb;
    shortterm short_term;

};


#endif //CS3502_DISPATCHER_H
