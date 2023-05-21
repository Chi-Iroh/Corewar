/*
** EPITECH PROJECT, 2023
** sti.c
** File description:
** -> sti mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

/*
@brief
    STI mnemonic :
        stores a register into memory (at specific index) or another register.
@param
    vm is the Virtual Machine
@param
    champion is the champion who executed the instruction
@param
    args are the arguments types and values
@returns
    true on success, false on failure
@note:
    sti REGISTER, REGISTER | DIRECT | INDIRECT, DIRECT | REGISTER
@note
    Doesn't change the carry.
*/
bool mnemonic_sti(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args)
{
    vm_register_t *register_address = NULL;
    uintmax_t arg2 = 0;
    uintmax_t arg3 = 0;
    vm_address_t memory_address = 0;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok(args), false);
    arg2 = mnemonic_get_arg(args, 1, champion);
    arg2 = mnemonic_get_indirect_address_value(vm, args.type[0], arg2);
    arg3 = mnemonic_get_arg(args, 2, champion);
    register_address = &champion->registers[args.args[0]];
    memory_address = champion->pc + (arg2 + arg3) % INDEX_MODULO;
    my_memcpy(register_address, &vm->memory[memory_address], REGISTER_SIZE);
    return true;
}
