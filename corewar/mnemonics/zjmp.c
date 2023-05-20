/*
** EPITECH PROJECT, 2023
** zjmp.c
** File description:
** -> st mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

bool mnemonic_zjmp(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args)
{
    uintmax_t arg1 = 0;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok(args), false);
    arg1 = mnemonic_get_arg(args, 0, champion);
    if (champion->carry == CARRY_ON) {
        champion->pc += arg1;
    }
    return true;
}
