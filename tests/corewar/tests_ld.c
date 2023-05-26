/*
** EPITECH PROJECT, 2023
** tests_ld.c
** File description:
** -> Tests for ld.c
*/

#include <string.h>
#include <criterion/criterion.h>
#include "../../include/my_macros.h"
#include "tests.h"

Test(mnemonic_ld, vm_null) {
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
        .mnemonic = "ld",
        .args = { 0, 1 },
        .type = { PARAMETER_DIRECT, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_LD)
    };
    cr_assert(!mnemonic_ld(NULL, &champion, args));
}

Test(mnemonic_ld, champion_null) {
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
        .mnemonic = "ld",
        .args = { 0, 1 },
        .type = { PARAMETER_DIRECT, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_LD)
    };
    cr_assert(!mnemonic_ld(&vm, NULL, args));
}

Test(mnemonic_ld, bad_args) {
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
        .op = &OP_TAB(MNEMONIC_LD)
    };
    cr_assert(!mnemonic_ld(&vm, &champion, args));
}

Test(mnemonic_ld, test_ld) {
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
        .mnemonic = "ld",
        .args = { 139, 1 },
        .type = { PARAMETER_DIRECT, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_LD)
    };
    printf("%s :\n", args.mnemonic);
    write_instruction(&vm, args, 0, false);
    cr_assert(mnemonic_ld(&vm, &champion, args));
    vm_register_t expected = args.args[0];
    printf("\tExpected : %X / Got : %X\n", expected, champion.registers[0]);
    cr_assert(champion.registers[args.args[1] - 1] == expected);

    args.type[0] = PARAMETER_INDIRECT;
    args.args[0] = 0 + 10;
    vm.memory[31] = 4;
    write_instruction(&vm, args, 0, true);
    cr_assert(mnemonic_ld(&vm, &champion, args));
    expected = (vm.memory[30] << 8) | vm.memory[31];
    printf("\tExpected : %X / Got : %X\n", expected, champion.registers[0]);
    cr_assert(champion.registers[args.args[1] - 1] == expected);

    args.args[0] += INDEX_MODULO;
    write_instruction(&vm, args, 0, true);
    cr_assert(mnemonic_ld(&vm, &champion, args));
    printf("\tExpected : %X / Got : %X\n", expected, champion.registers[0]);
    cr_assert(champion.registers[args.args[1] - 1] == expected);
}
