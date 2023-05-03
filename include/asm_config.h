/*
** EPITECH PROJECT, 2023
** config.h
** File description:
** -> Config header for build / tests
*/

#pragma once

#include <stdbool.h>

#ifdef STATIC_FUNCTION
    #undef STATIC_FUNCTION
#endif
#ifdef RUNNING_CRITERION_TESTS
    #define STATIC_FUNCTION

    // Declare any static function here.

    STATIC_FUNCTION bool asm_parser_is_arg_type_ok
        (char *arg, unsigned arg_i, unsigned op_tab_index);

    STATIC_FUNCTION unsigned asm_parser_op_tab_mnemonic_index(char *mnemonic);

    STATIC_FUNCTION bool asm_parser_get_next_word_impl
        (char *line, asm_parser_status_t *status, size_t *n,
        asm_parser_instruction_t *instruction);

    STATIC_FUNCTION asm_parser_instruction_t *asm_parser_get_next_word
        (char *line, asm_parser_status_t *status, size_t *n);

    STATIC_FUNCTION asm_parser_line_t *asm_parser_split_line(char *line);

#else
    #define STATIC_FUNCTION static
#endif

#ifdef ALWAYS_STATIC
    #undef ALWAYS_STATIC
#endif
#define ALWAYS_STATIC static
