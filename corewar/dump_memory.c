/*
** EPITECH PROJECT, 2023
** dump_memory.c
** File description:
** -> Dumps the memory
*/

#include "../include/my_macros.h"
#include "../include/my.h"
#include "../include/corewar/corewar.h"

void dump_memory(vm_t *vm)
{
    static const char *hex = "0123456789ABCDEF";

    RETURN_IF(!vm);
    for (vm_address_t i = 0; i < MEMORY_SIZE; i += 32) {
        for (unsigned j = 0; j < 32; j++) {
            my_printf("%c", hex[(vm->memory[i + j] & 0xF0) >> 4]);
            my_printf("%c", hex[vm->memory[i + j] & 0x0F]);
            my_putchar(j == 31 ? '\n' : ' ');
        }
    }
}
