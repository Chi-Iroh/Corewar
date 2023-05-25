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
    LFORK mnemonic : duplicates a champion and loads it at a given address,
        but wothout applying modulo on the memory address.
@param
    vm is the Virtual Machine
@param
    champion is the champion who executed the instruction
@param
    args are the arguments types and values
@returns
    true on success, false on failure
@note
    Doesn't change the carry.
*/
bool mnemonic_lfork(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args)
{
    uintmax_t arg1 = 0;
    vm_champion_t *duplicated = NULL;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok(args), false);
    arg1 = mnemonic_get_arg(args, 0, champion);
    champion_duplicate(vm, champion);
    duplicated = &vm->champions[vm->n_champions - 1];
    duplicated->load_address = champion->pc + arg1;
    return binary_load_at(vm, duplicated->filename, duplicated->load_address);
}
