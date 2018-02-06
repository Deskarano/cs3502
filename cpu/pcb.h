#ifndef CS3502_PCB_H
#define CS3502_PCB_H

typedef enum
{
    NEW,
    READY,
    RUNNING,
    BLOCKED,
    DONE
} pcb_state;

class pcb
{
public:
    pcb();

private:
    //cpu-related info
    unsigned int program_counter;
    unsigned int reg[16];

    //scheduler-related info
    pcb_state state;
    unsigned int priority;
};


#endif //CS3502_PCB_H
