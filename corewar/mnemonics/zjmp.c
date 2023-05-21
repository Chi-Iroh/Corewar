/*
** EPITECH PROJECT, 2023
** zjmp.c
** File description:
** -> st mnemonic
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

/*
@brief
    ZJMP mnemonic : jumps to an address only if carry is 1 (CARRY_ON).
@param
    vm is the Virtual Machine
@param
    champion is the champion who executed the instruction
@param
    args are the arguments types and values
@returns
    true on success, false on failure
@note:
    zjmp DIRECT
@note
    Doesn't change the carry.
@note
    If the parameter is a label as a direct value (%:label), then it's encoded
        as the number of bytes to jump.
    If the label's address is lower than the pc, then arg1 is something like
        0xFF'F5, which means pc must be decreased of its difference with
        0x01'00'00, here 11 bytes.
    Else, the arg1 will be something like 0x00'05, which means pc must be
        increased of 5 bytes.
    As the memory is much smaller than the max value fitting in 2 bytes
        (65535), then this notation isn"t ambiguous, if arg1 > MEM_SIZE,
        pc must be decreased, otherwise pc must be increased.
@note
    As the addresses are unsigned, if the zjmp causes the pc to overflow or
        underflow, it acts like applying a modulo MEMORY_SIZE.
*/
bool mnemonic_zjmp(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args)
{
    uintmax_t arg1 = 0;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok(args), false);
    arg1 = mnemonic_get_arg(args, 0, champion);
    if (champion->carry == CARRY_ON) {
        champion->pc = index_apply_to_pc(champion->pc, arg1, true);
    }
    return true;
}
