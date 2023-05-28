/*
** EPITECH PROJECT, 2023
** tests_lld.c
** File description:
** -> Tests for lld.c
*/

#include <string.h>
#include <criterion/criterion.h>
#include "../../include/my_macros.h"
#include "tests.h"

Test(mnemonic_lld, vm_null) {
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
        .mnemonic = "lld",
        .args = { 0, 1 },
        .type = {
            PARAMETER_DIRECT,
            PARAMETER_REGISTER
        },
        .op = &OP_TAB(MNEMONIC_LLD)
    };
    cr_assert(!mnemonic_lld(NULL, &champion, args));
}

Test(mnemonic_lld, champion_null) {
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
        .mnemonic = "lld",
        .args = { 0, 1 },
        .type = { PARAMETER_DIRECT, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_LLD)
    };
    cr_assert(!mnemonic_lld(&vm, NULL, args));
}

Test(mnemonic_lld, bad_args) {
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
        .op = &OP_TAB(MNEMONIC_LLD)
    };
    cr_assert(!mnemonic_lld(&vm, &champion, args));
}

Test(mnemonic_lld, test_lld) {
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
        .mnemonic = "lld",
        .args = { 139, 1 },
        .type = { PARAMETER_DIRECT, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_LLD)
    };
    printf("%s :\n", args.mnemonic);
    write_instruction(&vm, args, 0, false);
    cr_assert(mnemonic_lld(&vm, &champion, args));
    vm_register_t expected = args.args[0];
    printf("\tExpected : %X / Got : %X\n", expected, champion.registers[args.args[1] - 1]);
    cr_assert(champion.registers[args.args[1] - 1] == expected);

    args.type[0] = PARAMETER_INDIRECT;
    args.args[0] = 31 - REGISTER_SIZE + 1;
    write_instruction(&vm, args, 0, true);
    vm.memory[31] = 139;
    expected = 0;
    cr_assert(mnemonic_lld(&vm, &champion, args));
    for (unsigned i = REGISTER_SIZE - 1; ; i--) {
        expected <<= 8;
        expected |= vm.memory[31 - i];
        if (i == 0) {
            break;
        }
    }
    printf("\tExpected : %X / Got : %X\n", expected, champion.registers[args.args[1] - 1]);
    cr_assert(champion.registers[args.args[1] - 1] == expected);

    args.args[0] += INDEX_MODULO;
    write_instruction(&vm, args, 0, true);
    vm.memory[31] = 139;
    expected = 0;
    cr_assert(mnemonic_lld(&vm, &champion, args));
    for (unsigned i = REGISTER_SIZE - 1; ; i--) {
        expected <<= 8;
        expected |= vm.memory[31 - i];
        if (i == 0) {
            break;
        }
    }
    cr_assert(mnemonic_lld(&vm, &champion, args));
    printf("\tExpected : %X / Got : %X\n", expected, champion.registers[args.args[1] - 1]);
    cr_assert(champion.registers[args.args[1] - 1] == expected);
}
