/*
** EPITECH PROJECT, 2023
** exec_ld.c
** File description:
** -> ld instruction
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

bool mnemonic_ld(vm_t *vm, vm_champion_t *champion, vm_mnemonic_args_t args)
{
    vm_register_t *register_address = NULL;
    vm_address_t indirect_arg_address = 0;
    uint8_t *memory_address = NULL;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok("ld", args), false);
    register_address = &champion->registers[args.args[1]];
    if (args.args_type[0] == PARAMETER_DIRECT) {
        *register_address = args.args[0];
    } else {
        indirect_arg_address = (champion->pc + args.args[0]) % INDEX_MODULO;
        memory_address = &vm->memory[indirect_arg_address];
        my_memcpy(register_address, memory_address, REGISTER_SIZE);
    }
    return true;
}
