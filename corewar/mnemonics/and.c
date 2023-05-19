/*
** EPITECH PROJECT, 2023
** and.c
** File description:
** -> and mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

bool mnemonic_and(vm_t *vm, vm_champion_t *champion, vm_mnemonic_args_t args)
{
    vm_register_t sum = 0;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok("and", args), false);
    sum |= champion->registers[args.args[0]];
    sum &= champion->registers[args.args[1]];
    champion->registers[args.args[2]] = sum;
    champion->carry = sum == 0 ? CARRY_ON : CARRY_OFF;
    return true;
}
