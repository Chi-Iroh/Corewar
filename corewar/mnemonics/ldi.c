/*
** EPITECH PROJECT, 2023
** ldi.c
** File description:
** -> ldi mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

STATIC_FUNCTION vm_address_t get_memory_address
    (vm_address_t memory_addresses[2], vm_address_t pc)
{
    bool are_signs_inverse = false;

    are_signs_inverse |= memory_addresses[0] < pc && memory_addresses[1] > pc;
    are_signs_inverse |= memory_addresses[1] < pc && memory_addresses[0] > pc;
    if (are_signs_inverse) {
        return memory_addresses
            [ABS((intmax_t)memory_addresses[1] - pc) >
            ABS((intmax_t)memory_addresses[0] - pc)];
    }
    return memory_addresses[0] + memory_addresses[1];
}

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
    uintmax_t arg1 = 0;
    uintmax_t arg2 = 0;
    uintmax_t result = 0;
    vm_address_t memory_addresses[2] = {};
    vm_address_t memory_address = 0;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok(args), false);
    arg1 = mnemonic_get_arg(args, 0, champion);
    arg1 = mnemonic_get_indirect_address_value(vm, args.type[0], arg1);
    arg2 = mnemonic_get_arg(args, 1, champion);
    memory_addresses[0] = index_apply_to_pc(champion->pc, arg1, true);
    memory_addresses[1] = index_apply_to_pc(champion->pc, arg2, true);
    memory_address = get_memory_address(memory_addresses, champion->pc);
    memory_read_n_bytes(vm, memory_address, REGISTER_SIZE, &result);
    champion->registers[args.args[2] - 1] = result;
    champion->carry = result == 0 ? CARRY_ON : CARRY_OFF;
    return true;
}
