/*
** EPITECH PROJECT, 2023
** tests_lfork.c
** File description:
** -> Tests for lfork.c
*/

#include <string.h>
#include <criterion/criterion.h>
#include "../../include/my_macros.h"
#include "tests.h"

Test(mnemonic_lfork, vm_null) {
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
        .mnemonic = "lfork",
        .args = { 0, 1 },
        .type = { PARAMETER_DIRECT, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_LFORK)
    };
    cr_assert(!mnemonic_lfork(NULL, &champion, args));
}

Test(mnemonic_lfork, champion_null) {
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
        .champions = malloc(sizeof(vm_champion_t)),
        .memory = {},
        .n_champions = 1
    };
    vm.champions[0] = champion;
    vm_mnemonic_t args = {
        .mnemonic = "lfork",
        .args = { 0 },
        .type = { PARAMETER_DIRECT },
        .op = &OP_TAB(MNEMONIC_LFORK)
    };
    cr_assert(!mnemonic_lfork(&vm, NULL, args));
}

Test(mnemonic_lfork, bad_args) {
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
        .champions = malloc(sizeof(vm_champion_t)),
        .memory = {},
        .n_champions = 1
    };
    vm.champions[0] = champion;
    vm_mnemonic_t args = {
        .mnemonic = "",
        .args = { 0, 1 },
        .type = { PARAMETER_INDIRECT, PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_LFORK)
    };
    cr_assert(!mnemonic_lfork(&vm, vm.champions, args));
}

Test(mnemonic_lfork, test_lfork) {
    vm_champion_t champion = {
        .carry = CARRY_OFF,
        .filename = "../custom_champions/single_instruction.S.cor",
        .load_address = 0,
        .number = 0,
        .pc = 0,
        .registers = {},
        .size = 0,
    };
    vm_t vm = {
        .champions = malloc(sizeof(vm_champion_t)),
        .memory = {},
        .n_champions = 1
    };
    vm.champions[0] = champion;
    vm_mnemonic_t args = {
        .mnemonic = "lfork",
        .args = { 0 },
        .type = { PARAMETER_DIRECT },
        .op = &OP_TAB(MNEMONIC_LFORK)
    };
    printf("%s :\n", args.mnemonic);
    write_instruction(&vm, args, 0, false);
    bool r_value = mnemonic_lfork(&vm, &vm.champions[0], args);
    cr_assert(r_value);
    printf("\t%s\n", r_value ? "success" : "fail");
}
