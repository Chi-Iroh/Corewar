/*
** EPITECH PROJECT, 2023
** utils.c
** File description:
** -> Utilitiy functions for tests
*/

#include "tests.h"

void write_instruction(vm_t *vm, vm_mnemonic_t mnemonic, vm_address_t address, bool zero_init_all_memory)
{
    if (zero_init_all_memory) {
        memset(&vm->memory[0], 0, MEMORY_SIZE);
    }
    for (unsigned i = 0; i < N_OP; i++) {
        if (strcmp(op_tab[i].mnemonic, mnemonic.mnemonic) == 0) {
            vm->memory[address++] = op_tab[i].opcode;
            break;
        }
    }
    if (!MNEMONIC_HAS_NO_CODING_BYTE[mnemonic.op->opcode]) {
        vm->memory[address] = 0;
        for (unsigned i = 0; i < MAX_ARGS_NUMBER; i++) {
            vm->memory[address] <<= 2;
            vm->memory[address] |= ARG_NAME_TO_BITS[mnemonic.type[i]];
        }
        address++;
    }
    for (unsigned i = 0; i < MAX_ARGS_NUMBER; i++) {
        const unsigned arg_size = ARG_SIZE[mnemonic.type[i]];
        if (arg_size == 0) {
            break;
        }
        address += arg_size - 1;
        for (unsigned j = 0; j < arg_size; j++) {
            vm->memory[address--] = mnemonic.args[i] & 0xFF;
            mnemonic.args[i] >>= 8;
        }
        address += arg_size + 1;
    }
}
