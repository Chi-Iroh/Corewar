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

// mnemonic is not a pointer but a copy because this function is destructive
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
        address += arg_size + 1;
    }
}

void test_instruction(vm_t *vm, vm_mnemonic_t *mnemonic, vm_address_t address, bool zero_init_all_memory, char *comment) {
    write_instruction(vm, *mnemonic, address, true);
    puts("Memory :");
    dump_memory(vm, 1); // displays one line
    if (comment) {
        printf("%s :\n", comment);
    }
    *mnemonic = parse_instruction(vm, address);
    printf("mnemonic : %s\n", mnemonic->mnemonic);
    for (unsigned i = 0; i < MAX_ARGS_NUMBER; i++) {
        const unsigned arg_size = ARGS_SIZE[mnemonic->type[i]];

        if (arg_size != 0) {
            char format[256] = "%0";
            char result[256] = { 0 };
            sprintf(&format[strlen(&format[0])], "%d", arg_size * 2);
            strcpy(&format[strlen(&format[0])], "jX\n");
            sprintf(&result[0], &format[0], mnemonic->args[i]);
            printf("Arg %u : %ju (", i, mnemonic->args[i]);
            for (unsigned j = 0; j < arg_size; j++) {
                printf("%.2s", &result[j * 2]);
                if (j < arg_size - 1) {
                    putchar(' ');
                }
            }
            printf(")\n");
        }
        if (mnemonic->type[i] == PARAMETER_DIRECT) {
            printf("Direct value :");
        } else if (mnemonic->type[i] == PARAMETER_INDIRECT) {
            printf("Indirect value :");
        } else if (mnemonic->type[i] == PARAMETER_REGISTER) {
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

    test_instruction(&vm, &mnemonic, 0, true, "live %234");
    cr_assert_str_eq(mnemonic.mnemonic, "live");
    cr_assert(mnemonic.args[0] == 234);
    cr_assert(mnemonic.type[0] == PARAMETER_DIRECT);
    cr_assert(mnemonic.type[1] == PARAMETER_MAX);

    mnemonic.args[0] = 666;
    test_instruction(&vm, &mnemonic, 0, true, "live %666");
    cr_assert_str_eq(mnemonic.mnemonic, "live");
    cr_assert(mnemonic.args[0] == 666);
    cr_assert(mnemonic.type[0] == PARAMETER_DIRECT);
    cr_assert(mnemonic.type[1] == PARAMETER_MAX);
}

Test(exec_instruction, exec_instruction) {
    vm_champion_t champion = {
        .carry = CARRY_OFF,
        .filename = "notExistingFile.S",
        .load_address = 0,
        .number = 0,
        .pc = 0,
        .registers = {},
        .size = 0,
    };
    vm_t vm = {
        .champions = &champion,
        .memory = {},
        .n_champions = 1
    };
    vm_mnemonic_t ld = {
        .mnemonic = "ld",
        .args = { 0, 1 },
        .type = { PARAMETER_INDIRECT, PARAMETER_REGISTER },
        .op = &op_tab[0x01]
    };
    vm_address_t load_address = 0;
    write_instruction(&vm, ld, load_address, false);
    cr_assert(mnemonic_ld(&vm, &champion, ld));
    vm_register_t expected = 0;
    for (vm_address_t i = load_address; i < load_address + sizeof(expected); i++) {
        expected <<= 8;
        expected |= vm.memory[i];
    }
    printf("Expected : %X / Got : %X\n", expected, champion.registers[0]);
    cr_assert(champion.registers[0] == expected);
}
