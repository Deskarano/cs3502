#ifndef CS3502_PCB_NODE_H
#define CS3502_PCB_NODE_H

class pcb_node
{
public:
    explicit pcb_node(pcb *new_pcb)
    {
        this->next = nullptr;
        this->value = new_pcb;
    }

    pcb_node *next;
    pcb *value;
    unsigned int misc;
};

#endif //CS3502_PCB_NODE_H
