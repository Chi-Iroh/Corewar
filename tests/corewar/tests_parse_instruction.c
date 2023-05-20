/*
** EPITECH PROJECT, 2023
** parse_instruction.c
** File description:
** -> Tests for instruction parsing
*/

#include <criterion/criterion.h>
#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

Test(parse_instruction, parse_instruction) {
    vm_t vm = {};
    vm_mnemonic_t mnemonic = {};
    uint8_t live[MEMORY_SIZE] = {
        0x01, // live
        0b10'00'00'00, // direct, no, no, no
    };
    vm_direct_arg_t live_arg = 234;

    for (unsigned i = 0; i < DIRECT_SIZE; i++) {
        live[2 + DIRECT_SIZE - i - 1] = live_arg & 0xFF;
        live_arg >>= 8;
    }
    REASSIGN_STATIC_ARRAY(uint8_t, 2 + DIRECT_SIZE, vm.memory, live);
    puts("Memory :");
    dump_memory(&vm);
    puts("live %234 :");
    mnemonic = parse_instruction(&vm, 0);
    printf("mnemonic : %s\n", mnemonic.mnemonic);
    for (unsigned i = 0; i < MAX_ARGS_NUMBER; i++) {
        printf("Arg %u : %ju ", i, mnemonic.args[i]);
        if (mnemonic.type[i] == PARAMETER_DIRECT) {
            printf("Direct value");
        } else if (mnemonic.type[i] == PARAMETER_INDIRECT) {
            printf("Indirect value");
        } else if (mnemonic.type[i] == PARAMETER_REGISTER) {
            printf("Register value");
        } else {
            printf("No value");
        }
        for (unsigned j = 0; j < ARGS_SIZE[mnemonic.type[i]]; i++) {
            printf("%02x ", (unsigned)(mnemonic.args[i] & 0xFF));
            mnemonic.args[i] >>= 8;
        }
        putchar('\n');
    }
}
