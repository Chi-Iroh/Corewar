/*
** EPITECH PROJECT, 2023
** tests_fork.c
** File description:
** -> Tests for fork.c
*/

#include <string.h>
#include <criterion/criterion.h>
#include "../../include/my_macros.h"
#include "tests.h"

Test(mnemonic_fork, vm_null) {
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
        .mnemonic = "fork",
        .args = { 0 },
        .type = { PARAMETER_DIRECT },
        .op = &OP_TAB(MNEMONIC_FORK)
    };
    cr_assert(!mnemonic_fork(NULL, &champion, args));
}

Test(mnemonic_fork, champion_null) {
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
        .mnemonic = "fork",
        .args = { 0 },
        .type = { PARAMETER_DIRECT },
        .op = &OP_TAB(MNEMONIC_FORK)
    };
    cr_assert(!mnemonic_fork(&vm, NULL, args));
}

Test(mnemonic_fork, bad_args) {
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
        .op = &OP_TAB(MNEMONIC_FORK)
    };
    cr_assert(!mnemonic_fork(&vm, vm.champions, args));
}

Test(mnemonic_fork, test_fork) {
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
        .mnemonic = "fork",
        .args = { 0 },
        .type = { PARAMETER_DIRECT },
        .op = &OP_TAB(MNEMONIC_FORK)
    };
    printf("%s :\n", args.mnemonic);
    write_instruction(&vm, args, 0, false);
    bool r_value = mnemonic_fork(&vm, &vm.champions[0], args);
    cr_assert(r_value);
    printf("\t%s\n", r_value ? "success" : "fail");
}
