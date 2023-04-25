/*
** EPITECH PROJECT, 2023
** tests_parser_check_syntax.c
** File description:
** -> Unit testing for parser word syntax checking.
*/

#include <stdio.h>
#include <string.h>
#include <criterion/criterion.h>
#include <asm.h>

Test(check_syntax, mnemonic) {
    char buf[256] = { 0 };

    for (unsigned i = 0; i < LAST_OP; i++) {
        strcat(&buf[0], op_tab[i].mnemonique);
        strcat(&buf[0], " is a valid mnemonic");
        cr_expect(asm_parser_is_mnemonic(op_tab[i].mnemonique), "%s", &buf[0]);
        memset(&buf[0], 0, 256);
    }
    cr_expect(!asm_parser_is_mnemonic("LD"), "LD isn't a mnemonic");
    cr_expect(!asm_parser_is_mnemonic("lda"), "lda isn't a mnemonic");
    cr_expect(!asm_parser_is_mnemonic(NULL), "NULL isn't a mnemonic");
    cr_expect(!asm_parser_is_mnemonic(""), "an empty string isn't a mnemonic");
}

Test(chack_syntax, label) {
    cr_expect(asm_parser_is_label(":label"), ":label is a label");
    cr_expect(asm_parser_is_label(":label_42"), ":label_42 is a label");
    cr_expect(asm_parser_is_label(":42"), ":42 is a label");
    cr_expect(!asm_parser_is_label(":LABEL_42"), ":LABEL_42 isn't a label");
    cr_expect(!asm_parser_is_label(":"), ": isn't a label");
    cr_expect(!asm_parser_is_label("4"), "42 isn't a label");
    cr_expect(!asm_parser_is_label(""), "an empty string isn't a label");
    cr_expect(!asm_parser_is_label(NULL), "NULL isn't a label");
}

Test(check_syntax, direct_value) {
    cr_expect(asm_parser_is_direct_value("%4"), "%4 is a direct value");
    cr_expect(asm_parser_is_direct_value("%:label"), "%%:label is a direct value");
    cr_expect(asm_parser_is_direct_value("%:label_42"), "%%:label_42 is a direct value");
    cr_expect(!asm_parser_is_indirect_value("%:4"), "%%:4 isn't a direct value");
    cr_expect(!asm_parser_is_direct_value("%"), "%% isn't a direct value");
    cr_expect(!asm_parser_is_direct_value("%:"), "%%: isn't a direct value");
    cr_expect(!asm_parser_is_direct_value("%z"), "%%z isn't a direct value");
    cr_expect(!asm_parser_is_direct_value(""), "an empty string isn't a direct value");
    cr_expect(!asm_parser_is_direct_value(NULL), "NULL isn't a direct value");
}

Test(check_syntax, indirect_value) {
    cr_expect(asm_parser_is_indirect_value("4"), "4 is an indirect value");
    cr_expect(asm_parser_is_indirect_value(":label"), ":label is an indirect value");
    cr_expect(asm_parser_is_indirect_value(":label_42"), ":label_42 is an indirect value");
    cr_expect(asm_parser_is_indirect_value(":4"), ":4 is a indirect value");
    cr_expect(!asm_parser_is_indirect_value("%4"), "%%4 isn't an indirect value");
    cr_expect(!asm_parser_is_indirect_value("%:label"), "%%:label isn't an indirect value");
    cr_expect(!asm_parser_is_indirect_value(""), "an empty string isn't an indirect value");
    cr_expect(!asm_parser_is_indirect_value(NULL), "NULL isn't an indirect value");
}

Test(check_syntax, registers) {
    char buf[256] = { 'r' };

    sprintf(&buf[1], "%d", REG_NUMBER);
    cr_expect(asm_parser_is_register("r1"), "r1 is a register");
    cr_expect(asm_parser_is_register(&buf[0]), "%s is a register", &buf[0]);
    sprintf(&buf[1], "%d", REG_NUMBER + 1);
    cr_expect(!asm_parser_is_register(&buf[0]), "%s isn't a register", &buf[0]);
    cr_expect(!asm_parser_is_register("r0"), "r0 isn't a register");
    cr_expect(!asm_parser_is_register("R4"), "R4 isn't a register");
    cr_expect(!asm_parser_is_label("r1x"), "r1x isn't a register");
    cr_expect(!asm_parser_is_register("rg"), "rg isn't a register");
    cr_expect(!asm_parser_is_register("r"), "r isn't a register");
    cr_expect(!asm_parser_is_register(""), "an empty string isn't a register");
    cr_expect(!asm_parser_is_register(NULL), "NULL isn't a register");
}
