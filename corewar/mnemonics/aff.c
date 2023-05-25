/*
** EPITECH PROJECT, 2023
** aff.c
** File description:
** -> st mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/my.h"
#include "../../include/corewar/corewar.h"

/*
@brief
    AFF mnemonic : displays the value in a register as a char.
@param
    vm is the Virtual Machine
@param
    champion is the champion who executed the instruction
@param
    args are the arguments types and values
@returns
    true on success, false on failure
@note
    aff REGISTER
@note
    Doesn't change the carry.
*/
bool mnemonic_aff(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args)
{
    uintmax_t arg1 = 0;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok(args), false);
    arg1 = mnemonic_get_arg(args, 0, champion);
    my_putchar(champion->registers[arg1 - 1] % 0xFF);
    return true;
}
