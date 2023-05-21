/*
** EPITECH PROJECT, 2023
** or.c
** File description:
** -> or mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

/*
@brief
    XOR mnemonic : stores a bitwise XOR operation result into a register.
@param
    vm is the Virtual Machine
@param
    champion is the champion who executed the instruction
@param
    args are the arguments types and values
@returns
    true on success, false on failure
@note
    Sets the carry to 1 (CARRY_ON) if result is 0, otherwise to 0 (CARRY_OFF).
*/
bool mnemonic_xor(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args)
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
    result ^= arg2;
    champion->registers[args.args[2]] = result;
    champion->carry = result == 0 ? CARRY_ON : CARRY_OFF;
    return true;
}
