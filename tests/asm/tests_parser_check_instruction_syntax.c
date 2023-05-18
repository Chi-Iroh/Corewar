/*
** EPITECH PROJECT, 2023
** tests_parser_check_instruction_syntax.c
** File description:
** -> Tests for parser instruction syntax checking.
*/

#include <stdio.h>
#include <criterion/criterion.h>
#include "../../include/asm.h"

#define STRINGIFY_IMPL(x) #x
#define STRINGIFY(x) STRINGIFY_IMPL(x)
#define REG_MAX_STR "r" STRINGIFY(REG_NUMBER)

Test(check_instruction_syntax, get_mnemonic_index) {
    char buf[256] = { 0 };

    for (unsigned i = 0; i < LAST_OP; i++) {
        sprintf(&buf[0], "%s is the %u-th mnemonic", op_tab[i].mnemonique, i);
        cr_expect(asm_parser_op_tab_mnemonic_index(op_tab[i].mnemonique) == i, "%s", &buf[0]);
        memset(&buf[0], 0, 256);
    }
    cr_expect(asm_parser_op_tab_mnemonic_index("helloworld") == N_OP, "helloworld isn't a mnemonic (out-of-bounds index expected)");
    cr_expect(asm_parser_op_tab_mnemonic_index(NULL) == N_OP, "NULL isn't a mnemonic (out-of-bounds index expected)");
    cr_expect(asm_parser_op_tab_mnemonic_index("") == N_OP, "empty string isn't a mnemonic (out-of-bounds index expected)");
    cr_expect(asm_parser_op_tab_mnemonic_index("addj") == N_OP, "addj isn't a mnemonic (out-of-bounds index expected)");
}

Test(check_instruction_syntax, check_arg_type) {
    char *arg_types[ARG_TYPE_MAX] = {
        [T_DIR] = "T_DIR",
        [T_IND] = "T_IND",
        [T_LAB] = "T_LAB",
        [T_REG] = "T_REG"
    };
    char *arg_examples[ARG_TYPE_MAX][4] = {
        [T_DIR] = { "%142", "%49", "%:goto_is_fun", "%:helloworld" },
        [T_IND] = { "139", ":goto_is_fun", ":helloworld", "0" },
        [T_LAB] = { "label", "goto_is_fun", "helloworld", "coredumped" },
        [T_REG] = { "r1", "r5", "r8", REG_MAX_STR }
    };
    char buf[256] = { 0 };
    char *mnemonic_str = NULL;
    int type_val = 0;

    for (unsigned mnemonic = 0; mnemonic < LAST_OP; mnemonic++) {
        mnemonic_str = op_tab[mnemonic].mnemonique;

        for (unsigned arg = 0; arg <= op_tab[mnemonic].nbr_args; arg++) {

            // arg 0 = mnemonic
            if (arg == 0) {
                sprintf(&buf[0], "%s is a correct 0-th argument for %s", mnemonic_str, mnemonic_str);
                cr_expect(asm_parser_is_arg_type_ok(mnemonic_str, arg, mnemonic), "%s", &buf[0]);
                memset(&buf[0], 0, 256);
                continue;
            }
            for (unsigned type = 0; type < 4; type++) {
                type_val = asm_parser_word_types[type];

                // if expected type
                if ((op_tab[mnemonic].type[arg - 1] & type_val)) {
                    for (unsigned example = 0; example < 4; example++) {
                        sprintf(&buf[0], "%s(%s) is a correct %u-th arg for mnemonic %s", arg_examples[type_val][example], arg_types[type_val], arg, mnemonic_str);
                        cr_expect(asm_parser_is_arg_type_ok(arg_examples[type_val][example], arg, mnemonic), "%s", &buf[0]);
                        memset(&buf[0], 0, 256);
                    }
                } else {
                    for (unsigned example = 0; example < 4; example++) {
                        sprintf(&buf[0], "%s(%s) isn't a correct %u-th arg for mnemonic %s", arg_examples[type_val][example], arg_types[type_val], arg, mnemonic_str);
                        cr_expect(!asm_parser_is_arg_type_ok(arg_examples[type_val][example], arg, mnemonic), "%s", &buf[0]);
                        memset(&buf[0], 0, 256);
                    }
                }
            }
        }
    }
}

Test(check_instruction_syntax, check_instruction) {
    char *arg_types[ARG_TYPE_MAX] = {
        [T_DIR] = "T_DIR",
        [T_IND] = "T_IND",
        [T_LAB] = "T_LAB",
        [T_REG] = "T_REG"
    };
    char *arg_examples_ok[ARG_TYPE_MAX][4] = {
        [T_DIR] = { "%142", "%49", "%:goto_is_fun", "%:helloworld" },
        [T_IND] = { "139", ":goto_is_fun", ":helloworld", "0" },
        [T_LAB] = { "label", "goto_is_fun", "helloworld", "coredumped" },
        [T_REG] = { "r1", "r5", "r8", REG_MAX_STR }
    };
    char *arg_examples_nok[ARG_TYPE_MAX][4] = {
        [T_DIR] = { "142", "%:49", ":goto_is_fun", REG_MAX_STR },
        [T_IND] = { "%139", "r1", "%:helloworld", "%:0" },
        [T_LAB] = { ":label", "%:goto_is_fun", "r3", "%49" },
        [T_REG] = { "%4", ":hello", "%:world", "45" }
    };
    asm_parser_instruction_t arg4;
    asm_parser_instruction_t arg3;
    asm_parser_instruction_t arg2;
    asm_parser_instruction_t arg1;
    asm_parser_instruction_t mnemonic;
    asm_parser_instruction_t *instruction[5] = {
        &mnemonic,
        &arg1,
        &arg2,
        &arg3,
        &arg4,
    };
    char buf[256] = { 0 };

    arg4 = (asm_parser_instruction_t) {
        .next = NULL,
        .previous = &arg3
    };
    arg3 = (asm_parser_instruction_t) {
        .next = &arg4,
        .previous = &arg2
    };
    arg2 = (asm_parser_instruction_t) {
        .next = &arg3,
        .previous = &arg1
    };
    arg1 = (asm_parser_instruction_t) {
        .next = &arg2,
        .previous = &arg3
    };
    mnemonic = (asm_parser_instruction_t) {
        .next = &arg1,
        .previous = NULL
    };
    op_t *op = NULL;

    for (unsigned mnemonic = 0; mnemonic < LAST_OP; mnemonic++) {
        op = &op_tab[mnemonic];
        instruction[0]->word = op->mnemonique;
        for (unsigned ok_example = 0; ok_example < 4; ok_example++) {
            for (unsigned arg = 1; arg <= op->nbr_args; arg++) {
                for (unsigned arg_type_index = 0; arg_type_index < ASM_PARSER_WORD_TYPES; arg_type_index++) {
                    if ((op->type[arg - 1] & asm_parser_word_types[arg_type_index])) {
                        instruction[arg]->word = arg_examples_ok[asm_parser_word_types[arg_type_index]][ok_example];
                        break;
                    }
                }
                instruction[op->nbr_args]->next = NULL;
            }
            sprintf(&buf[0], "%s, %s, %s, %s, %s is correct", instruction[0]->word, instruction[1]->word, instruction[2]->word, instruction[3]->word, instruction[4]->word);
            cr_expect(asm_parser_check_instruction_syntax(instruction[0]), "%s", &buf[0]);
            memset(&buf[0], 0, 256);
            instruction[0]->next = instruction[1];
            for (unsigned i = 1; i <= 5; i++) {
                instruction[i]->word = NULL;
                instruction[i]->next = (i == 5) ? NULL : instruction[i + 1];
            }
        }
        for (unsigned nok_example = 0; nok_example < 4; nok_example++) {
            for (unsigned arg = 1; arg < op_tab[mnemonic].nbr_args; arg++) {
                for (unsigned arg_type_index = 0; arg_type_index < ASM_PARSER_WORD_TYPES; arg_type_index++) {
                    if ((op_tab[mnemonic].type[arg - 1] & asm_parser_word_types[arg_type_index])) {
                        instruction[arg]->word = arg_examples_nok[asm_parser_word_types[arg_type_index]][nok_example];
                    }
                }
            }
            sprintf(&buf[0], "%s, %s, %s, %s, %s isn't correct", instruction[0]->word, instruction[1]->word, instruction[2]->word, instruction[3]->word, instruction[4]->word);
            cr_expect(!asm_parser_check_instruction_syntax(instruction[0]), "%s", &buf[0]);
            memset(&buf[0], 0, 256);
            instruction[0]->next = instruction[1];
            for (unsigned i = 1; i <= 5; i++) {
                instruction[i]->word = NULL;
                instruction[i]->next = (i == 5) ? NULL : instruction[i + 1];
            }
        }
    }

}
