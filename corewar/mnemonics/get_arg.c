/*
** EPITECH PROJECT, 2023
** get_arg.c
** File description:
** -> Properly reads an arg as a register, direct or indirect value
*/

#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

/*
@brief
    Converts the arg according to its type.
@param
    arg is the arg to convert
@param
    type is its type (every value not PARAMETER_DIRECT/INDIRECT/REGISTER)
        is considered incorrect
@param
    champion is the champion process (needed to access registers)
@param
    status is a possibly NULL pointer which is used to store whether the
        arg is valid or not.
@returns
    either a register, a memory address or the arg itself
        whether the type is PARAMETER_REGISTER, INDIRECT or DIRECT
@returns
    UINTMAX_MAX is also returned on error
@note
    an indirect type means returning (program counter + arg) % INDEX_MODULO.
*/
uintmax_t mnemonic_get_arg
    (vm_mnemonic_args_t args, unsigned index, vm_champion_t *champion)
{
    if (index >= MAX_ARGS_NUMBER) {
        return UINTMAX_MAX;
    }
    if (args.type[index] == PARAMETER_REGISTER) {
        if (args.args[index] < REGISTERS_NUMBER) {
            return champion->registers[args.args[index]];
        }
    } else if (args.type[index] == PARAMETER_INDIRECT) {
        return champion->pc + (args.args[index] % INDEX_MODULO);
    }
    return args.type[index] == PARAMETER_DIRECT ?
        args.args[index] : UINTMAX_MAX;
}
