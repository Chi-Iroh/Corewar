/*
** EPITECH PROJECT, 2023
** tests_live.c
** File description:
** -> Tests for live.c
*/

#include <string.h>
#include <criterion/criterion.h>
#include "../../include/my_macros.h"
#include "tests.h"

Test(mnemonic_live, vm_null) {
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
        .mnemonic = "live",
        .args = { 0 },
        .type = { PARAMETER_DIRECT },
        .op = &OP_TAB(MNEMONIC_LIVE)
    };
    cr_assert(!mnemonic_live(NULL, &champion, args));
}

Test(mnemonic_live, champion_null) {
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
        .mnemonic = "live",
        .args = { 0 },
        .type = { PARAMETER_DIRECT },
        .op = &OP_TAB(MNEMONIC_LIVE)
    };
    cr_assert(!mnemonic_live(&vm, NULL, args));
}

Test(mnemonic_live, bad_args) {
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
        .op = &OP_TAB(MNEMONIC_LIVE)
    };
    cr_assert(!mnemonic_live(&vm, &champion, args));
}

Test(mnemonic_live, test_live) {
    vm_champion_t champion = {
        .carry = CARRY_OFF,
        .filename = "notExistingFile.S",
        .load_address = 0,
        .number = 0,
        .pc = 0,
        .registers = {},
        .size = 0,
        .is_alive = false
    };
    vm_t vm = {
        .champions = &champion,
        .memory = {},
        .n_champions = 1,
        .n_lives = 0
    };
    vm_mnemonic_t args = {
        .mnemonic = "live",
        .args = { 0 },
        .type = { PARAMETER_DIRECT },
        .op = &OP_TAB(MNEMONIC_LIVE)
    };
    vm_address_t load_address = 0;
    const unsigned n_lives = vm.n_lives;
    printf("%s :\n", args.mnemonic);
    write_instruction(&vm, args, load_address, false);
    cr_assert(mnemonic_live(&vm, &champion, args));
    cr_assert(champion.is_alive);
    cr_assert(vm.n_lives == n_lives + 1);
}
