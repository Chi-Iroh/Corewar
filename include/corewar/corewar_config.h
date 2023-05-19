/*
** EPITECH PROJECT, 2023
** asm_config.h
** File description:
** -> Config header for VM build / tests
*/

#pragma once

#include <stdbool.h>

#ifdef STATIC_FUNCTION
    #undef STATIC_FUNCTION
#endif
#ifdef RUNNING_CRITERION_TESTS
    #define STATIC_FUNCTION

    #include "corewar_types.h"

    // Declare any static function here.

#else
    #define STATIC_FUNCTION static
#endif
