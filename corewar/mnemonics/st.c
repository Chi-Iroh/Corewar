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
    uintmax_t arg1 = 0;
    uintmax_t arg2 = 0;
    uint8_t *memory_address = NULL;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok(args), false);
    arg1 = mnemonic_get_arg(args, 0, champion);
    if (args.type[1] == PARAMETER_REGISTER) {
        champion->registers[args.args[1] - 1] = arg1;
    } else {
        arg2 = mnemonic_get_arg(args, 1, champion);
        memory_address = &vm->memory[champion->pc + (arg2 % INDEX_MODULO)];
        for (vm_address_t i = 0; i < REGISTER_SIZE; i++) {
            memory_address[REGISTER_SIZE - i - 1] = arg1 % 0xFF;
            arg1 >>= 8;
        }
    }
    return true;
}
