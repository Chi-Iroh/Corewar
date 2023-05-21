/*
** EPITECH PROJECT, 2023
** sub.c
** File description:
** -> sub mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

/*
@brief
    SUB mnemonic :
        substracts two registers and writes the sum into a third one.
@param
    vm is the Virtual Machine
@param
    champion is the champion who executed the instruction
@param
    args are the arguments types and values
@returns
    true on success, false on failure
@note:
    sub REGISTER, REGISTER, REGISTER
@note
    Sets the carry to 1 (CARRY_ON) if result is 0, otherwise to 0 (CARRY_OFF).
*/
bool mnemonic_sub(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args)
{
    vm_register_t sum = 0;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok(args), false);
    sum += mnemonic_get_arg(args, 0, champion);
    sum -= mnemonic_get_arg(args, 1, champion);
    champion->registers[args.args[2]] = sum;
    champion->carry = sum == 0 ? CARRY_ON : CARRY_OFF;
    return true;
}
