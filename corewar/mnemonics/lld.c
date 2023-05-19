/*
** EPITECH PROJECT, 2023
** lld.c
** File description:
** -> lld mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

bool mnemonic_lld(vm_t *vm, vm_champion_t *champion, vm_mnemonic_args_t args)
{
    vm_register_t *register_address = NULL;
    uintmax_t arg1 = 0;
    uint8_t *memory_address = NULL;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok("lld", args), false);
    arg1 = mnemonic_get_arg(args, 0, champion);
    register_address = &champion->registers[args.args[1]];
    if (args.type[0] == PARAMETER_DIRECT) {
        *register_address = args.args[0];
    } else {
        memory_address = &vm->memory[champion->pc + arg1];
        my_memcpy(register_address, memory_address, REGISTER_SIZE);
    }
    champion->carry = args.args[0] == 0 ? CARRY_ON : CARRY_OFF;
    return true;
}
