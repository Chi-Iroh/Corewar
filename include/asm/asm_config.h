/*
** EPITECH PROJECT, 2023
** asm_config.h
** File description:
** -> Config header for ASM build / tests
*/

#pragma once

#include <stdbool.h>

#ifdef STATIC_FUNCTION
    #undef STATIC_FUNCTION
#endif
#ifdef RUNNING_CRITERION_TESTS
    #define STATIC_FUNCTION

    #include "asm_types.h"

    // Declare any static function here.

    STATIC_FUNCTION bool parser_is_arg_type_ok
        (char *arg, unsigned arg_i, unsigned op_tab_index);

    STATIC_FUNCTION unsigned parser_op_tab_mnemonic_index(char *mnemonic);

    STATIC_FUNCTION bool parser_get_next_word_impl
        (char *line, parser_status_t *status, size_t *n,
        parser_instruction_t *instruction);

    STATIC_FUNCTION parser_line_t *parser_split_line(char *line);

    STATIC_FUNCTION bool parser_check_instruction_syntax
        (parser_instruction_t *instruction);

    STATIC_FUNCTION void parser_remove_single_instruction_comma
        (parser_instruction_t *instruction);

    STATIC_FUNCTION bool parser_add_line
        (char *line, parser_line_t **file);

#else
    #define STATIC_FUNCTION static
#endif
