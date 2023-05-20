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

    STATIC_FUNCTION size_t binary_get_size(int fd);

    STATIC_FUNCTION bool binary_open
    (vm_t *vm, char *binary,
    vm_champion_t *champion, vm_address_t load_address);

    STATIC_FUNCTION char *mnemonic_get_from_opcode(uint8_t opcode);

    STATIC_FUNCTION bool mnemonic_get_args
    (vm_t *vm, vm_address_t address, vm_mnemonic_t *mnemonic);

    STATIC_FUNCTION bool mnemonic_get_args
        (vm_t *vm, vm_address_t address, vm_mnemonic_t *mnemonic);

#else
    #define STATIC_FUNCTION static
#endif
