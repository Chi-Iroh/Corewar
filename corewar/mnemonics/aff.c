/*
** EPITECH PROJECT, 2023
** st.c
** File description:
** -> st mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/my.h"
#include "../../include/corewar/corewar.h"

bool mnemonic_aff(vm_t *vm, vm_champion_t *champion, vm_mnemonic_args_t args)
{
    uintmax_t arg1 = 0;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok("aff", args), false);
    arg1 = mnemonic_get_arg(args, 0, champion);
    my_putchar(champion->registers[arg1] % 0xFF);
    return true;
}
