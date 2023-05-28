/*
** EPITECH PROJECT, 2023
** tests_lldi.c
** File description:
** -> Tests for lldi.c
*/

#include <string.h>
#include <criterion/criterion.h>
#include "../../include/my_macros.h"
#include "tests.h"

Test(mnemonic_lldi, vm_null) {
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
        .mnemonic = "lldi",
        .args = { 0, 1 },
        .type = { PARAMETER_REGISTER, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_LLDI)
    };
    cr_assert(!mnemonic_lldi(NULL, &champion, args));
}

Test(mnemonic_lldi, champion_null) {
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
        .mnemonic = "lldi",
        .args = { 0, 1 },
        .type = { PARAMETER_REGISTER, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_LLDI)
    };
    cr_assert(!mnemonic_lldi(&vm, NULL, args));
}

Test(mnemonic_lldi, bad_args) {
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
        .op = &OP_TAB(MNEMONIC_LLDI)
    };
    cr_assert(!mnemonic_lldi(&vm, &champion, args));
}

Test(mnemonic_lldi, test_lldi) {
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
        .mnemonic = "lldi",
        .args = { 24, 4, 1 },
        .type = { PARAMETER_DIRECT, PARAMETER_DIRECT, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_LLDI)
    };
    printf("%s :\n", args.mnemonic);

    write_instruction(&vm, args, 0, true);
    vm.memory[31] = 139;
    vm_register_t expected = 0;
    cr_assert(mnemonic_lldi(&vm, &champion, args));
    for (unsigned i = REGISTER_SIZE - 1; ; i--) {
        expected <<= 8;
        expected |= vm.memory[31 - i];
        if (i == 0) {
            break;
        }
    }
    printf("\tExpected : %X / Got : %X\n", expected, champion.registers[args.args[2] - 1]);
    cr_assert(champion.registers[args.args[2] - 1] == expected);
}
