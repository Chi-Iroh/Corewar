/*
** EPITECH PROJECT, 2023
** tests_add.c
** File description:
** -> Tests for add.c
*/

#include <string.h>
#include <criterion/criterion.h>
#include "../../include/my_macros.h"
#include "tests.h"

Test(mnemonic_add, vm_null) {
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
        .mnemonic = "add",
        .args = { 1, 2, 3 },
        .type = { PARAMETER_REGISTER, PARAMETER_REGISTER, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_ADD)
    };
    cr_assert(!mnemonic_add(NULL, &champion, args));
}

Test(mnemonic_add, champion_null) {
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
        .mnemonic = "add",
        .args = { 1, 2, 3 },
        .type = { PARAMETER_REGISTER, PARAMETER_REGISTER, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_ADD)
    };
    cr_assert(!mnemonic_add(&vm, NULL, args));
}

Test(mnemonic_add, bad_args) {
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
        .op = &OP_TAB(MNEMONIC_ADD)
    };
    cr_assert(!mnemonic_add(&vm, &champion, args));
}

Test(mnemonic_add, test_add) {
    vm_champion_t champion = {
        .carry = CARRY_OFF,
        .filename = "notExistingFile.S",
        .load_address = 0,
        .number = 0,
        .pc = 0,
        .registers = { 1, 7 },
        .size = 0,
    };
    vm_t vm = {
        .champions = &champion,
        .memory = {},
        .n_champions = 1
    };
    vm_mnemonic_t args = {
        .mnemonic = "add",
        .args = { 1, 2, 3 },
        .type = { PARAMETER_REGISTER, PARAMETER_REGISTER, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_ADD)
    };
    vm_address_t load_address = 0;
    printf("%s :\n", args.mnemonic);
    write_instruction(&vm, args, load_address, false);
    cr_assert(mnemonic_add(&vm, &champion, args));
    const vm_register_t expected = champion.registers[0] + champion.registers[1];
    printf("\tExpected : %X / Got : %X\n", expected, champion.registers[args.args[2] - 1]);
    cr_assert(champion.registers[args.args[2] - 1] == expected);
}
