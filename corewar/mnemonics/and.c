/*
** EPITECH PROJECT, 2023
** and.c
** File description:
** -> and mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

bool mnemonic_and(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args)
{
    vm_register_t result = 0;
    uintmax_t arg1 = 0;
    uintmax_t arg2 = 0;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok(args), false);
    arg1 = mnemonic_get_arg(args, 0, champion);
    arg1 = mnemonic_get_indirect_address_value(vm, args.type[0], arg1);
    arg2 = mnemonic_get_arg(args, 1, champion);
    arg2 = mnemonic_get_indirect_address_value(vm, args.type[1], arg2);
    result |= arg1;
    result &= arg2;
    champion->registers[args.args[2]] = result;
    champion->carry = result == 0 ? CARRY_ON : CARRY_OFF;
    return true;
}
