/*
** EPITECH PROJECT, 2023
** ldi.c
** File description:
** -> ldi mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

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
