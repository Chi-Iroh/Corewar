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
    LLDI mnemonic : loads the sum of two values into a register,
        but without applying modulo to the memory address.
@param
    vm is the Virtual Machine
@param
    champion is the champion who executed the instruction
@param
    args are the arguments types and values
@returns
    true on success, false on failure
@note
    lldi REGISTER | DIRECT | INDIRECT, DIRECT | INDIRECT, REGISTER
@note
    Sets the carry to 1 (CARRY_ON) if value is 0, otherwise to 0 (CARRY_OFF).
*/
bool mnemonic_lldi(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args)
{
    vm_register_t *register_address = NULL;
    uintmax_t arg1 = 0;
    uintmax_t arg2 = 0;
    vm_address_t memory_address = 0;
    vm_indirect_arg_t tmp = 0;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok(args), false);
    arg1 = mnemonic_get_arg(args, 0, champion);
    arg1 = mnemonic_get_indirect_address_value(vm, args.type[0], arg1);
    arg2 = mnemonic_get_arg(args, 1, champion);
    memory_address = index_apply_to_pc(champion->pc, arg1, false);
    memory_read_n_bytes(vm, &memory_address, INDIRECT_SIZE, (uintmax_t*)&tmp);
    tmp = arg2 > MEMORY_SIZE ? tmp - (0x01'00'00 - arg2) : tmp + arg2;
    memory_address = index_apply_to_pc(champion->pc, tmp, false);
    register_address = &champion->registers[args.args[2] - 1];
    my_memcpy(register_address, &vm->memory[memory_address], REGISTER_SIZE);
    champion->carry = vm->memory[memory_address] == 0 ? CARRY_ON : CARRY_OFF;
    return true;
}
