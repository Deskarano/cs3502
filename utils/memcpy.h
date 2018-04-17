#ifndef CS3502_MEMCPY_H
#define CS3502_MEMCPY_H

void disk_to_ram(unsigned int disk_addr, unsigned int ram_addr, unsigned int num_words, unsigned int requester);
void ram_to_disk(unsigned int ram_addr, unsigned int disk_addr, unsigned int num_words, unsigned int requester);

#endif //CS3502_MEMCPY_H
