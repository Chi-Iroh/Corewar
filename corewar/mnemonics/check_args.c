/*
** EPITECH PROJECT, 2023
** check_args.c
** File description:
** -> Checks if mnemonic args are valid or not
*/

#include "../../include/my.h"
#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

STATIC_FUNCTION unsigned mnemonic_get_op_tab_index(char *mnemonic)
{
    RETURN_VALUE_IF(!mnemonic, N_OP);
    for (unsigned i = 0; i < LAST_OP; i++) {
        if (my_strcmp(mnemonic, op_tab[i].mnemonique) == 0) {
            return i;
        }
    }
    return N_OP;
}

bool mnemonic_are_args_ok(char *mnemonic, vm_mnemonic_args_t args)
{
    const unsigned mnemonic_index = mnemonic_get_op_tab_index(mnemonic);

    for (unsigned i = 0; i < op_tab[mnemonic_index].nbr_args; i++) {
        if (!(op_tab[mnemonic_index].type[i] & args.type[i])) {
            return false;
        }
        if (args.type[i] == PARAMETER_REGISTER) {
            RETURN_VALUE_IF(args.args[i] > REGISTERS_NUMBER, false);
        }
    }
    return true;
}
