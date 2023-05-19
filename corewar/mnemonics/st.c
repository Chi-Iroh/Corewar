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
    uintmax_t arg1 = 0;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok("st", args), false);
    arg1 = mnemonic_get_arg(args, 0, champion);
    register_address = &champion->registers[args.args[0]];
    if (args.type[1] == PARAMETER_REGISTER) {
        *register_address = champion->registers[args.args[1]];
    } else {
        my_memcpy(&vm->memory[arg1], register_address, REGISTER_SIZE);
    }
    return true;
}
