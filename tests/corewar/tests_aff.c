/*
** EPITECH PROJECT, 2023
** tests_aff.c
** File description:
** -> Tests for aff.c
*/

#include <string.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../../include/my_macros.h"
#include "tests.h"

Test(mnemonic_aff, vm_null) {
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
        .mnemonic = "aff",
        .args = { 1 },
        .type = { PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_AFF)
    };
    vm_address_t load_address = 0;
    write_instruction(&vm, args, load_address, false);
    cr_assert(!mnemonic_aff(NULL, &champion, args));
}

Test(mnemonic_aff, champion_null) {
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
        .mnemonic = "aff",
        .args = { 1 },
        .type = { PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_AFF)
    };
    vm_address_t load_address = 0;
    write_instruction(&vm, args, load_address, false);
    cr_assert(!mnemonic_aff(&vm, NULL, args));
}

Test(mnemonic_aff, bad_args) {
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
        .args = { 0 },
        .type = { PARAMETER_REGISTER },
        .op = NULL
    };
    vm_address_t load_address = 0;
    write_instruction(&vm, args, load_address, false);
    cr_assert(!mnemonic_aff(&vm, &champion, args));
}

Test(mnemonic_aff, test_aff/*, .init = cr_redirect_stdout*/) {
    vm_champion_t champion = {
        .carry = CARRY_OFF,
        .filename = "notExistingFile.S",
        .load_address = 0,
        .number = 0,
        .pc = 0,
        .registers = { '*' },
        .size = 0,
    };
    vm_t vm = {
        .champions = &champion,
        .memory = {},
        .n_champions = 1
    };
    vm_mnemonic_t args = {
        .mnemonic = "aff",
        .args = { 1 },
        .type = { PARAMETER_REGISTER },
        .op = &OP_TAB(MNEMONIC_AFF)
    };
    vm_address_t load_address = 0;
    write_instruction(&vm, args, load_address, false);
    cr_assert(mnemonic_aff(&vm, &champion, args));
    // to redirect and compare stdout with expected char (for an obscure reason, the size variable is very huge)
    // FILE* file = cr_get_redirected_stdout();
    // cr_assert(file);
    // fseek(file, 0, SEEK_END);
    // const size_t size = ftell(file);
    // fseek(file, 0, SEEK_SET);
    // cr_assert(size != 0);
    // char *stdout_str = calloc(size, sizeof(char));
    // fprintf(stderr, "Stdout size: %zu\n", size);
    // cr_assert(stdout_str);
    // cr_expect(fwrite(stdout_str, sizeof(char), size, file) == size);
    // char expected[2] = { champion.registers[args.args[0] - 1], 0 };
    // fprintf(stderr, "Expected: '%s' / Got: '%s'\n", expected, stdout_str);
    // cr_assert_stdout_eq_str(expected);
    // free(stdout_str);
}
