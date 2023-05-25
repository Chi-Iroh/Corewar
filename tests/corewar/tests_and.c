/*
** EPITECH PROJECT, 2023
** parse_instruction.c
** File description:
** -> Tests for and.c
*/

#include <string.h>
#include <criterion/criterion.h>
#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

// mnemonic is not a pointer but a copy because this function is destructive
static void write_instruction(vm_t *vm, vm_mnemonic_t mnemonic, vm_address_t address, bool zero_init_all_memory)
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
    vm->memory[address] = 0;
    for (unsigned i = 0; i < MAX_ARGS_NUMBER; i++) {
        vm->memory[address] <<= 2;
        vm->memory[address] |= ARG_NAME_TO_BITS[mnemonic.type[i]];
    }
    address++;
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

Test(mnemonic_and, vm_null) {
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
    vm_mnemonic_t args = {
        .mnemonic = "and",
        .args = { 0, 1, 2 },
        .type = { PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT },
        .op = &op_tab[MNEMONIC_LIVE]
    };
    vm_address_t load_address = 0;
    write_instruction(&vm, args, load_address, false);
    cr_assert(!mnemonic_and(NULL, &champion, args));
}

Test(mnemonic_and, champion_null) {
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
    vm_mnemonic_t args = {
        .mnemonic = "and",
        .args = { 0, 1, 2 },
        .type = { PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT },
        .op = &op_tab[MNEMONIC_LIVE]
    };
    vm_address_t load_address = 0;
    write_instruction(&vm, args, load_address, false);
    cr_assert(!mnemonic_and(&vm, NULL, args));
}

Test(mnemonic_and, bad_args) {
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
    vm_mnemonic_t args = {
        .mnemonic = "",
        .args = { 0, 1 },
        .type = { PARAMETER_INDIRECT, PARAMETER_REGISTER },
        .op = NULL
    };
    vm_address_t load_address = 0;
    write_instruction(&vm, args, load_address, false);
    cr_assert(!mnemonic_and(&vm, &champion, args));
}

Test(mnemonic_and, test_and) {
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
    vm_mnemonic_t args = {
        .mnemonic = "and",
        .args = { 0, 1, 2 },
        .type = { PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT },
        .op = &op_tab[MNEMONIC_LIVE]
    };
    vm_address_t load_address = 0;
    write_instruction(&vm, args, load_address, false);
    cr_assert(mnemonic_and(&vm, &champion, args));
    vm_register_t expected = 0;
    for (vm_address_t i = load_address; i < load_address + sizeof(expected); i++) {
        expected <<= 8;
        expected |= vm.memory[i];
    }
    printf("Expected : %X / Got : %X\n", expected, champion.registers[0]);
    cr_assert(champion.registers[0] == expected);
}
