/*
** EPITECH PROJECT, 2023
** tests_xor.c
** File description:
** -> Tests for xor.c
*/

#include <string.h>
#include <criterion/criterion.h>
#include "../../include/my_macros.h"
#include "tests.h"

Test(mnemonic_xor, vm_null) {
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
        .mnemonic = "xor",
        .args = { 1, 2, 3 },
        .type = { PARAMETER_REGISTER, PARAMETER_REGISTER, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_XOR)
    };
    cr_assert(!mnemonic_xor(NULL, &champion, args));
}

Test(mnemonic_xor, champion_null) {
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
        .mnemonic = "xor",
        .args = { 1, 2, 3 },
        .type = { PARAMETER_REGISTER, PARAMETER_REGISTER, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_XOR)
    };
    cr_assert(!mnemonic_xor(&vm, NULL, args));
}

Test(mnemonic_xor, bad_args) {
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
        .op = &OP_TAB(MNEMONIC_XOR)
    };
    cr_assert(!mnemonic_xor(&vm, &champion, args));
}

Test(mnemonic_xor, test_xor) {
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
        .mnemonic = "xor",
        .args = { 1, 2, 3 },
        .type = { PARAMETER_REGISTER, PARAMETER_REGISTER, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_XOR)
    };
    vm_address_t load_address = 0;
    write_instruction(&vm, args, load_address, false);
    cr_assert(mnemonic_xor(&vm, &champion, args));
    const vm_register_t expected = champion.registers[0] ^ champion.registers[1];
    printf("Expected : %X / Got : %X\n", expected, champion.registers[0]);
    cr_assert(champion.registers[args.args[2] - 1] == expected);
}
