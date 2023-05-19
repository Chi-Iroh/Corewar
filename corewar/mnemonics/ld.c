/*
** EPITECH PROJECT, 2023
** ld.c
** File description:
** -> ld mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

bool mnemonic_ld(vm_t *vm, vm_champion_t *champion, vm_mnemonic_args_t args)
{
    vm_register_t *register_address = NULL;
    uintmax_t arg1 = 0;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok("ld", args), false);
    arg1 = mnemonic_get_arg(args, 0, champion);
    register_address = &champion->registers[args.args[1]];
    if (args.type[0] == PARAMETER_DIRECT) {
        *register_address = args.args[0];
    } else {
        my_memcpy(&vm->memory[arg1], register_address, REGISTER_SIZE);
    }
    champion->carry = args.args[0] == 0 ? CARRY_ON : CARRY_OFF;
    return true;
}
