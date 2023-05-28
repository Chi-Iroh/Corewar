/*
** EPITECH PROJECT, 2023
** tests_ldi.c
** File description:
** -> Tests for ldi.c
*/

#include <string.h>
#include <criterion/criterion.h>
#include "../../include/my_macros.h"
#include "tests.h"

Test(mnemonic_ldi, vm_null) {
    vm_champion_t champion = {
        .carry = CARRY_OFF,
        .filename = "notExistingFile.S",
        .load_address = 0,
        .number = 0,
        .pc = 0,
        .registers = {},
        .size = 0,
    };
    vm_mnemonic_t args = {
        .mnemonic = "ldi",
        .args = { 1, 1 },
        .type = { PARAMETER_REGISTER, PARAMETER_DIRECT },
        .op = &OP_TAB(MNEMONIC_LDI)
    };
    cr_assert(!mnemonic_ldi(NULL, &champion, args));
}

Test(mnemonic_ldi, champion_null) {
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
        .mnemonic = "ldi",
        .args = { 1, 1 },
        .type = { PARAMETER_REGISTER, PARAMETER_DIRECT },
        .op = &OP_TAB(MNEMONIC_LDI)
    };
    cr_assert(!mnemonic_ldi(&vm, NULL, args));
}

Test(mnemonic_ldi, bad_args) {
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
    cr_assert(!mnemonic_ldi(&vm, &champion, args));
}

Test(mnemonic_ldi, test_ldi) {
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
        .mnemonic = "ldi",
        .args = { 139, 4, 1 },
        .type = { PARAMETER_DIRECT, PARAMETER_DIRECT, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_LDI)
    };
    printf("%s :\n", args.mnemonic);
    write_instruction(&vm, args, 0, false);
    cr_assert(mnemonic_ldi(&vm, &champion, args));
    vm_register_t expected = args.args[0] + args.args[1];
    printf("\tExpected : %X / Got : %X\n", expected, champion.registers[args.args[2] - 1]);
    cr_assert(champion.registers[args.args[2] - 1] == expected);

    args.type[0] = PARAMETER_INDIRECT;
    args.args[0] = 31 - REGISTER_SIZE + 1;
    write_instruction(&vm, args, 0, true);
    vm.memory[31] = 139;
    expected = 0;
    cr_assert(mnemonic_ldi(&vm, &champion, args));
    for (unsigned i = REGISTER_SIZE - 1; ; i--) {
        expected <<= 8;
        expected |= vm.memory[31 - i];
        if (i == 0) {
            break;
        }
    }
    printf("\tExpected : %X / Got : %X\n", expected, champion.registers[args.args[2] - 1]);
    cr_assert(champion.registers[args.args[2] - 1] == expected);

    args.args[0] += INDEX_MODULO;
    write_instruction(&vm, args, 0, true);
    vm.memory[31] = 139;
    expected = 0;
    cr_assert(mnemonic_ldi(&vm, &champion, args));
    for (unsigned i = REGISTER_SIZE - 1; ; i--) {
        expected <<= 8;
        expected |= vm.memory[31 - i];
        if (i == 0) {
            break;
        }
    }
    cr_assert(mnemonic_ldi(&vm, &champion, args));
    printf("\tExpected : %X / Got : %X\n", expected, champion.registers[args.args[2] - 1]);
    cr_assert(champion.registers[args.args[2] - 1] == expected);
}
