/*
** EPITECH PROJECT, 2023
** st.c
** File description:
** -> st mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

/*
@brief
    ST mnemonic : stores a register into memory or another register.
@param
    vm is the Virtual Machine
@param
    champion is the champion who executed the instruction
@param
    args are the arguments types and values
@returns
    true on success, false on failure
@note:
    st REGISTER, DIRECT | INDIRECT
@note
    Doesn't change the carry.
*/
bool mnemonic_st(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args)
{
    vm_register_t *register_address = NULL;
    uintmax_t arg1 = 0;
    uint8_t *memory_address = NULL;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok(args), false);
    arg1 = mnemonic_get_arg(args, 0, champion);
    register_address = &champion->registers[args.args[0] - 1];
    if (args.type[1] == PARAMETER_REGISTER) {
        *register_address = champion->registers[args.args[1] - 1];
    } else {
        memory_address = &vm->memory[champion->pc + (arg1 % INDEX_MODULO)];
        my_memcpy(memory_address, register_address, REGISTER_SIZE);
    }
    return true;
}
