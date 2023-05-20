/*
** EPITECH PROJECT, 2023
** get_indirect_address_value.c
** File description:
** -> Gets the value in memory at the address represented by an indirect value
*/

#include "../../include/corewar/corewar.h"

uintmax_t mnemonic_get_indirect_address_value
    (vm_t *vm, mnemonic_parameter_t type, uintmax_t value)
{
    if (type == PARAMETER_INDIRECT) {
        return vm->memory[value];
    }
    return value;
}
