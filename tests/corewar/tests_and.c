/*
** EPITECH PROJECT, 2023
** tests_and.c
** File description:
** -> Tests for and.c
*/

#include <string.h>
#include <criterion/criterion.h>
#include "../../include/my_macros.h"
#include "tests.h"

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
    vm_mnemonic_t args = {
        .mnemonic = "and",
        .args = { 1, 2, 3 },
        .type = { PARAMETER_REGISTER, PARAMETER_REGISTER, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_AND)
    };
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
        .args = { 1, 2, 3 },
        .type = { PARAMETER_REGISTER, PARAMETER_REGISTER, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_AND)
    };
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
        .op = &OP_TAB(MNEMONIC_AND)
    };
    cr_assert(!mnemonic_and(&vm, &champion, args));
}

Test(mnemonic_and, test_and) {
    vm_champion_t champion = {
        .carry = CARRY_OFF,
        .filename = "notExistingFile.S",
        .load_address = 0,
        .number = 0,
        .pc = 0,
        .registers = { 0b100, 0b101 },
        .size = 0,
    };
    vm_t vm = {
        .champions = &champion,
        .memory = {},
        .n_champions = 1
    };
    vm_mnemonic_t args = {
        .mnemonic = "and",
        .args = { 1, 2, 3 },
        .type = { PARAMETER_REGISTER, PARAMETER_REGISTER, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_AND)
    };
    vm_address_t load_address = 0;
    printf("%s :\n", args.mnemonic);
    write_instruction(&vm, args, load_address, false);
    cr_assert(mnemonic_and(&vm, &champion, args));
    const vm_register_t expected = champion.registers[0] & champion.registers[1];
    printf("\tExpected : %X / Got : %X\n", expected, champion.registers[0]);
    cr_assert(champion.registers[args.args[2] - 1] == expected);
}
