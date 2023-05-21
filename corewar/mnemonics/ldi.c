/*
** EPITECH PROJECT, 2023
** ldi.c
** File description:
** -> ldi mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

/*
@brief
    LDI mnemonic : loads the sum of two values into a register.
@param
    vm is the Virtual Machine
@param
    champion is the champion who executed the instruction
@param
    args are the arguments types and values
@returns
    true on success, false on failure
@note
    ldi REGISTER | DIRECT | INDIRECT, DIRECT | INDIRECT, REGISTER
@note
    Sets the carry to 1 (CARRY_ON) if value is 0, otherwise to 0 (CARRY_OFF).
*/
bool mnemonic_ldi(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args)
{
    vm_register_t *register_address = NULL;
    uintmax_t arg1 = 0;
    uintmax_t arg2 = 0;
    vm_address_t memory_address = 0;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok(args), false);
    arg1 = mnemonic_get_arg(args, 0, champion);
    arg1 = mnemonic_get_indirect_address_value(vm, args.type[0], arg1);
    arg2 = mnemonic_get_arg(args, 1, champion);
    register_address = &champion->registers[args.args[2]];
    memory_address = champion->pc + (arg1 + arg2) % INDEX_MODULO;
    my_memcpy(register_address, &vm->memory[memory_address], REGISTER_SIZE);
    champion->carry = vm->memory[memory_address] == 0 ? CARRY_ON : CARRY_OFF;
    return true;
}
