/*
** EPITECH PROJECT, 2023
** parser_check_syntax.c
** File description:
** -> Unit testing for parser word syntax checking.
*/

#include <stdio.h>
#include <string.h>
#include <criterion/criterion.h>
#include "../../include/asm/asm.h"

Test(check_word_syntax, mnemonic) {
    char buf[256] = { 0 };

    for (unsigned i = 0; i < LAST_OP; i++) {
        sprintf(&buf[0], "%s is a valid mnemonic", op_tab[i].mnemonic);
        cr_expect(parser_is_mnemonic(op_tab[i].mnemonic), "%s", &buf[0]);
        memset(&buf[0], 0, 256);
    }
    cr_expect(!parser_is_mnemonic("LD"), "LD isn't a mnemonic");
    cr_expect(!parser_is_mnemonic("lda"), "lda isn't a mnemonic");
    cr_expect(!parser_is_mnemonic(NULL), "NULL isn't a mnemonic");
    cr_expect(!parser_is_mnemonic(""), "an empty string isn't a mnemonic");
}

static const char *const colon_pos_name[LABEL_COLON_MAX] = {
    "LABEL_COLON_BEGIN",
    "LABEL_COLON_END",
    "LABEL_COLON_NONE"
};

void test_label(char *str, parser_label_colon_pos_t valid_colon_pos) {
    for (parser_label_colon_pos_t colon_pos = 0; colon_pos < LABEL_COLON_MAX; colon_pos++) {
        const bool expected_return_value = colon_pos == valid_colon_pos;
        const char *error_msg = expected_return_value ? "is a label" : "isn't a label";

        cr_expect(expected_return_value == parser_is_label(str, colon_pos), "%s %s (%s)", str, error_msg, colon_pos_name[colon_pos]);
    }
}

Test(check_word_syntax, label) {
    for (parser_label_colon_pos_t colon_pos = 0; colon_pos < LABEL_COLON_MAX; colon_pos++) {
        cr_expect(!parser_is_label(":LABEL_42", colon_pos), ":LABEL_42 isn't a label (%s)", colon_pos_name[colon_pos]);
        cr_expect(!parser_is_label(":", colon_pos), ": isn't a label (%s)", colon_pos_name[colon_pos]);
        cr_expect(!parser_is_label("", colon_pos), "an empty string isn't a label (%s)", colon_pos_name[colon_pos]);
        cr_expect(!parser_is_label(NULL, colon_pos), "NULL isn't a label (%s)", colon_pos_name[colon_pos]);
    }
    test_label(":label", LABEL_COLON_BEGIN);
    test_label(":label_42", LABEL_COLON_BEGIN);
    test_label(":42", LABEL_COLON_BEGIN);

    test_label("label:", LABEL_COLON_END);
    test_label("label_42:", LABEL_COLON_END);
    test_label("42:", LABEL_COLON_END);

    test_label("label", LABEL_COLON_NONE);
    test_label("label_42", LABEL_COLON_NONE);
    test_label("42", LABEL_COLON_NONE);
}

Test(check_word_syntax, direct_value) {
    cr_expect(parser_is_direct_value("%4"), "%4 is a direct value");
    cr_expect(parser_is_direct_value("%:label"), "%%:label is a direct value");
    cr_expect(parser_is_direct_value("%:label_42"), "%%:label_42 is a direct value");
    cr_expect(!parser_is_indirect_value("%:4"), "%%:4 isn't a direct value");
    cr_expect(!parser_is_direct_value("%"), "%% isn't a direct value");
    cr_expect(!parser_is_direct_value("%:"), "%%: isn't a direct value");
    cr_expect(!parser_is_direct_value("%z"), "%%z isn't a direct value");
    cr_expect(!parser_is_direct_value(""), "an empty string isn't a direct value");
    cr_expect(!parser_is_direct_value(NULL), "NULL isn't a direct value");
}

Test(check_word_syntax, indirect_value) {
    cr_expect(parser_is_indirect_value("4"), "4 is an indirect value");
    cr_expect(parser_is_indirect_value(":label"), ":label is an indirect value");
    cr_expect(parser_is_indirect_value(":label_42"), ":label_42 is an indirect value");
    cr_expect(parser_is_indirect_value(":4"), ":4 is a indirect value");
    cr_expect(!parser_is_indirect_value("%4"), "%%4 isn't an indirect value");
    cr_expect(!parser_is_indirect_value("%:label"), "%%:label isn't an indirect value");
    cr_expect(!parser_is_indirect_value(""), "an empty string isn't an indirect value");
    cr_expect(!parser_is_indirect_value(NULL), "NULL isn't an indirect value");
}

Test(check_word_syntax, registers) {
    char buf[256] = { 'r' };

    for (unsigned i = 1; i <= REGISTERS_NUMBER; i++) {
        sprintf(&buf[1], "%u", i);
        cr_expect(parser_is_register(&buf[0]), "%s is a register", &buf[0]);
        memset(&buf[1], 0, 255);
    }
    sprintf(&buf[1], "%d", REGISTERS_NUMBER + 1);
    cr_expect(!parser_is_register(&buf[0]), "%s isn't a register", &buf[0]);
    cr_expect(!parser_is_register("r0"), "r0 isn't a register");
    cr_expect(!parser_is_register("R4"), "R4 isn't a register");
    cr_expect(!parser_is_register("r1x"), "r1x isn't a register");
    cr_expect(!parser_is_register("rg"), "rg isn't a register");
    cr_expect(!parser_is_register("r"), "r isn't a register");
    cr_expect(!parser_is_register(""), "an empty string isn't a register");
    cr_expect(!parser_is_register(NULL), "NULL isn't a register");
}
