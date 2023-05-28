/*
** EPITECH PROJECT, 2023
** binary_load_all.c
** File description:
** -> Loads all binary from command line
*/

#include "../include/my.h"
#include "../include/corewar/corewar.h"

/*
@brief
    Initializes the Virtual Machine and loads all the binaries from
        command-line.
@param
    vm is the Virtual Machine
@param
    argc is the number of command-line arguments
@param
    argv are the command-line arguments
@returns
    false on error, true otherwise
@note
    The Virtual Machine MUSTN'T be initialized when calling this function,
        otherwise there will be a memory leak.
*/
bool binary_load_all(vm_t *vm, unsigned argc, char *argv[])
{
    bool status = vm_init(vm, argv);

    parse_argv(vm, argc, argv);
    for (unsigned i = 1; i < argc && status; i++) {
        if (!argv[i]) {
            break;
        }
        status &= binary_argv_load_single_binary(vm, argc, argv, &i);
        vm->n_champions += status;
    }
    return status;
}
