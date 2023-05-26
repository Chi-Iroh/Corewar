/*
** EPITECH PROJECT, 2023
** tests_check_args.c
** File description:
** -> Tests for check_args.c
*/

#include <criterion/criterion.h>
#include "tests.h"

Test(arg_validity, all) {
    cr_assert(mnemonic_are_args_ok(
        (vm_mnemonic_t) {
            .mnemonic = "live",
            .args = { 139 },
            .type = { PARAMETER_DIRECT },
            .op = &OP_TAB(MNEMONIC_LIVE)
        }
    ));
}
