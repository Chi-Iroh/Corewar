/*
** EPITECH PROJECT, 2023
** parse_instruction.c
** File description:
** -> Tests for instruction parsing
*/

#include <string.h>
#include <criterion/criterion.h>
#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

void write_instruction(vm_t *vm, vm_mnemonic_t mnemonic, vm_address_t address, bool zero_init_all_memory)
{
    if (zero_init_all_memory) {
        memset(&vm->memory[0], 0, MEMORY_SIZE);
    }
    for (unsigned i = 0; i < LAST_OP; i++) {
        if (strcmp(op_tab[i].mnemonic, mnemonic.mnemonic) == 0) {
            vm->memory[address++] = op_tab[i].opcode;
            break;
        }
    }
    vm->memory[address] = 0;
    for (unsigned i = 0; i < MAX_ARGS_NUMBER; i++) {
        vm->memory[address] <<= 2;
        vm->memory[address] |= ARGS_NAME_TO_BITS[mnemonic.type[i]];
    }
    address++;
    for (unsigned i = 0; i < MAX_ARGS_NUMBER; i++) {
        const unsigned arg_size = ARGS_SIZE[mnemonic.type[i]];
        if (arg_size == 0) {
            break;
        }
        address += arg_size - 1;
        for (unsigned j = 0; j < arg_size; j++) {
            vm->memory[address--] = mnemonic.args[i] & 0xFF;
            mnemonic.args[i] >>= 8;
        }
        address += arg_size;
    }
}

void test_instruction(vm_t *vm, vm_mnemonic_t mnemonic, vm_address_t address, bool zero_init_all_memory, char *comment) {
    write_instruction(vm, mnemonic, address, true);
    puts("Memory :");
    dump_memory(vm, 1); // displays one line
    if (comment) {
        printf("%s :\n", comment);
    }
    mnemonic = parse_instruction(vm, address);
    printf("mnemonic : %s\n", mnemonic.mnemonic);
    for (unsigned i = 0; i < MAX_ARGS_NUMBER; i++) {
        const unsigned arg_size = ARGS_SIZE[mnemonic.type[i]];

        if (arg_size != 0) {
            char format[256] = "%0";
            char result[256] = { 0 };
            sprintf(&format[strlen(&format[0])], "%d", arg_size * 2);
            strcpy(&format[strlen(&format[0])], "jX\n");
            sprintf(&result[0], &format[0], mnemonic.args[i]);
            printf("Arg %u : %ju (", i, mnemonic.args[i]);
            for (unsigned j = 0; j < arg_size; j++) {
                printf("%.2s", &result[j * 2]);
                if (j < arg_size - 1) {
                    putchar(' ');
                }
            }
            printf(")\n");
        }
        if (mnemonic.type[i] == PARAMETER_DIRECT) {
            printf("Direct value :");
        } else if (mnemonic.type[i] == PARAMETER_INDIRECT) {
            printf("Indirect value :");
        } else if (mnemonic.type[i] == PARAMETER_REGISTER) {
            printf("Register value :");
        } else {
            printf("No value");
        }
        putchar('\n');
    }
    putchar('\n');
}

Test(parse_instruction, parse_instruction) {
    vm_t vm = {};
    vm_mnemonic_t mnemonic = {
        .mnemonic = "live",
        .args = { 234 },
        .type = { PARAMETER_DIRECT }
    };

    test_instruction(&vm, mnemonic, 0, true, "live %234");
    mnemonic.args[0] = 666;
    test_instruction(&vm, mnemonic, 0, true, "live %666");
}
