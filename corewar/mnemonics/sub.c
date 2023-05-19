/*
** EPITECH PROJECT, 2023
** sub.c
** File description:
** -> add mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

bool mnemonic_sub(vm_t *vm, vm_champion_t *champion, vm_mnemonic_args_t args)
{
    vm_register_t difference = 0;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok("sub", args), false);
    difference += champion->registers[args.args[0]];
    difference -= champion->registers[args.args[1]];
    champion->registers[args.args[2]] = difference;
    champion->carry = difference == 0 ? CARRY_ON : CARRY_OFF;
    return true;
}
