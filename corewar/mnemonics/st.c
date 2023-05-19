/*
** EPITECH PROJECT, 2023
** st.c
** File description:
** -> st mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

bool mnemonic_st(vm_t *vm, vm_champion_t *champion, vm_mnemonic_args_t args)
{
    vm_register_t *register_address = NULL;
    vm_address_t indirect_arg_address = 0;
    uint8_t *memory_address = NULL;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok("st", args), false);
    register_address = &champion->registers[args.args[0]];
    if (args.args_type[1] == PARAMETER_REGISTER) {
        *register_address = champion->registers[args.args[1]];
    } else {
        indirect_arg_address = (champion->pc + args.args[0]) % INDEX_MODULO;
        memory_address = &vm->memory[indirect_arg_address];
        my_memcpy(memory_address, register_address, REGISTER_SIZE);
    }
    return true;
}
