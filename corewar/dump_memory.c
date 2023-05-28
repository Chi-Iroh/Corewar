/*
** EPITECH PROJECT, 2023
** dump_memory.c
** File description:
** -> Dumps the memory
*/

#include "../include/my_macros.h"
#include "../include/my.h"
#include "../include/corewar/corewar.h"

const char *const PRINTF_COLOR_RED = "\x1b[31m";
const char *const PRINTF_COLOR_GREEN = "\x1b[32m";
const char *const PRINTF_COLOR_CYAN = "\x1b[36m";
const char *const PRINTF_COLOR_RESET = "\x1b[0m";

STATIC_FUNCTION void dump_get_address_prefix_for_printf(char prefix[32])
{
    my_memset(&prefix[0], 0, 32);
    my_strcpy(&prefix[0], PRINTF_COLOR_CYAN);
    my_strcat(&prefix[0], "0x%0.");
    my_sput_nbr(sizeof(vm_address_t) * 2, &prefix[my_strlen(&prefix[0])]);
    my_strcat(&prefix[0], "X\t:\t");
    my_strcat(&prefix[0], PRINTF_COLOR_RESET);
}

STATIC_FUNCTION void dump_print_byte(uint8_t byte)
{
    static const char *hex = "0123456789ABCDEF";

    if (byte == 0x00) {
        my_printf("%s", PRINTF_COLOR_RED);
    } else {
        my_printf("%s", PRINTF_COLOR_GREEN);
    }
    my_printf("%c", hex[(byte & 0xF0) >> 4]);
    my_printf("%c", hex[byte & 0x0F]);
    my_printf("%s", PRINTF_COLOR_RESET);
}

/*
@brief
    Dumps the memory (32 hex space-separated bytes per line).
@param
    vm is the Virtual Machine
@param
    n_32_bytes_chunks is the number of chunks (thus, lines) to display.
    0 displays the whole memory, n displays n chunks.
@note
    If n_32bytes_chunks is greater than the number of chunks in memory,
        displays the whole memory (similar than 0).
*/
void dump_memory(vm_t *vm, unsigned n_32bytes_chunks)
{
    const unsigned n_32bytes_chunks_in_mem =
        MEMORY_SIZE / 32 + MEMORY_SIZE % 32;
    const vm_address_t n_32bytes_dumped_chunks = n_32bytes_chunks == 0 ?
        n_32bytes_chunks_in_mem :
        MIN(n_32bytes_chunks, n_32bytes_chunks_in_mem);
    char prefix[32] = {};

    RETURN_IF(!vm);
    dump_get_address_prefix_for_printf(prefix);
    for (vm_address_t i = 0; i < 32 * n_32bytes_dumped_chunks; i += 32) {
        my_printf(&prefix[0], i);
        for (unsigned j = 0; j < 32; j++) {
            dump_print_byte(vm->memory[i + j]);
            my_putchar(j == 31 ? '\n' : ' ');
        }
    }
}

void dump_memory_once(vm_t *vm, unsigned n_32bytes_chunks)
{
    static bool is_first_call = true;

    if (is_first_call) {
        dump_memory(vm, n_32bytes_chunks);
        is_first_call = false;
    }
}
