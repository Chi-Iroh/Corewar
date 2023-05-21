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
    Searches the -dump flag (load address) in argv.
@param
    argv are command-line arguments
@param
    index is the index where beginning searching
@param
    vm is the Virtual Machine
@returns
    true if flag -dump is found, otherwise false
@note
    The syntax MUST be valid when calling this function !
*/
STATIC_FUNCTION bool binary_argv_search_dump
    (vm_t *vm, char *argv[], unsigned *index)
{
    const unsigned copy_index = *index;

    vm->must_dump_memory = false;
    while (argv[*index] && parse_argv_is_flag(argv[*index])) {
        if (my_strcmp(argv[*index], "-dump") == 0) {
            vm->must_dump_memory = true;
            vm->cycles_before_memory_dump = my_getnbr(argv[*index + 1]);
            *index += 2;
            return true;
        }
        (*index)++;
    }
    *index = copy_index;
    return false;
}

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
        while (binary_argv_search_dump(vm, argv, &i)) {

        }
        if (!argv[i]) {
            break;
        }
        status &= binary_argv_load_single_binary(vm, argc, argv, &i);
    }
    return status;
}
