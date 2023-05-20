/*
** EPITECH PROJECT, 2023
** dump_memory.c
** File description:
** -> Dumps the memory
*/

#include "../include/my_macros.h"
#include "../include/my.h"
#include "../include/corewar/corewar.h"

/*
@brief
    Dumps the memory (32 hex space-separated bytes per line).
@param
    vm is the Virtual Machine
@param
    n_32_bytes_chunks is the number of chunks (thus, lines) to display.
    0 displays the whole memory, n displays n chunks.
@note
    If n_32bytes_chunks it greater than the number of chunks in memory,
        displays the whole memory (similar than 0).
*/
void dump_memory(vm_t *vm, unsigned n_32bytes_chunks)
{
    static const char *hex = "0123456789ABCDEF";
    const unsigned n_32bytes_chunks_in_mem =
        MEMORY_SIZE / 32 + MEMORY_SIZE % 32;
    vm_address_t dumped_bytes = n_32bytes_chunks == 0 ?
        n_32bytes_chunks_in_mem :
        32 * MIN(n_32bytes_chunks, n_32bytes_chunks_in_mem);

    RETURN_IF(!vm);
    for (vm_address_t i = 0; i < dumped_bytes; i += 32) {
        for (unsigned j = 0; j < 32; j++) {
            my_printf("%c", hex[(vm->memory[i + j] & 0xF0) >> 4]);
            my_printf("%c", hex[vm->memory[i + j] & 0x0F]);
            my_putchar(j == 31 ? '\n' : ' ');
        }
    }
}
