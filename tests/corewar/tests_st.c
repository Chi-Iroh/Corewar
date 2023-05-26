/*
** EPITECH PROJECT, 2023
** tests_st.c
** File description:
** -> Tests for st.c
*/

#include <string.h>
#include <criterion/criterion.h>
#include "../../include/my_macros.h"
#include "tests.h"

Test(mnemonic_st, vm_null) {
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
        .mnemonic = "st",
        .args = { 1, 2 },
        .type = { PARAMETER_REGISTER, PARAMETER_DIRECT },
        .op = &OP_TAB(MNEMONIC_ST)
    };
    cr_assert(!mnemonic_st(NULL, &champion, args));
}

Test(mnemonic_st, champion_null) {
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
        .mnemonic = "st",
        .args = { 1, 2 },
        .type = { PARAMETER_REGISTER, PARAMETER_DIRECT },
        .op = &OP_TAB(MNEMONIC_ST)
    };
    cr_assert(!mnemonic_st(&vm, NULL, args));
}

Test(mnemonic_st, bad_args) {
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
        .op = &OP_TAB(MNEMONIC_ST)
    };
    cr_assert(!mnemonic_st(&vm, &champion, args));
}

Test(mnemonic_st, test_st) {
    vm_champion_t champion = {
        .carry = CARRY_OFF,
        .filename = "notExistingFile.S",
        .load_address = 0,
        .number = 0,
        .pc = 0,
        .registers = { 139 },
        .size = 0,
    };
    vm_t vm = {
        .champions = &champion,
        .memory = {},
        .n_champions = 1
    };
    vm_mnemonic_t args = {
        .mnemonic = "st",
        .args = { 1, 31 - REGISTER_SIZE + 1 },
        .type = { PARAMETER_REGISTER, PARAMETER_INDIRECT },
        .op = &OP_TAB(MNEMONIC_ST)
    };
    printf("%s :\n", args.mnemonic);
    write_instruction(&vm, args, 0, false);
    cr_assert(mnemonic_st(&vm, &champion, args));
    vm_register_t expected = champion.registers[args.args[0] - 1];
    vm_register_t got = 0;
    for (vm_address_t i = args.args[1] % INDEX_MODULO; i < (args.args[1] % INDEX_MODULO) + REGISTER_SIZE; i++) {
        got <<= 8;
        got |= vm.memory[i];
    }
    printf("\tExpected : %X / Got : %X\n", expected, got);
    cr_expect(got == expected);

    args.type[1] = PARAMETER_REGISTER;
    args.args[1] = 2;
    write_instruction(&vm, args, 0, true);
    cr_assert(mnemonic_st(&vm, &champion, args));
    printf("\tExpected : %X / Got : %X\n", expected, champion.registers[args.args[1] - 1]);
    cr_expect(expected == champion.registers[args.args[1] - 1]);
}
