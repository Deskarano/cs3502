//
// Created by drew on 3/7/2018.
//

#ifndef CS3502_PCB_NODE_H
#define CS3502_PCB_NODE_H

class pcb_node
{
public:
    explicit pcb_node(pcb *new_pcb)
    {
        this->next = nullptr;
        this->pcb = new_pcb;
    }

    pcb_node *next;
    pcb *pcb;
};

#endif //CS3502_PCB_NODE_H
