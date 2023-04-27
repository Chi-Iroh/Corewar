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

    STATIC_FUNCTION bool asm_parser_is_arg_type_ok
    (char *arg, unsigned arg_i, unsigned op_tab_index);

    STATIC_FUNCTION unsigned asm_parser_op_tab_mnemonic_index(char *mnemonic);
#else
    #define STATIC_FUNCTION static
#endif
