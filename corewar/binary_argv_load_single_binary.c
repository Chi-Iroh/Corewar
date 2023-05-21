/*
** EPITECH PROJECT, 2023
** binary_load_argv.c
** File description:
** -> Loads a binary file with argv flags.
*/

#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/corewar/corewar.h"

/*
@brief
    Searches the binary filename in argv.
@param
    argv are command-line arguments
@param
    index is the index where beginning searching
@returns
    next binary filename
@note
    The syntax MUST be valid when calling this function !
*/
STATIC_FUNCTION char *binary_argv_search_filename
    (char *argv[], unsigned index)
{
    while (argv[index] && parse_argv_is_flag(argv[index])) {
        index += 2;
    }
    return argv[index];
}

STATIC_FUNCTION void binary_argv_handle_flags_before_load_binary
    (char *argv[], unsigned *index,
    vm_address_t *load_address, vm_address_t *prog_number)
{
    vm_address_t *params[2] = { load_address, prog_number };
    bool is_load_address_flag = false;
    bool is_prog_number_flag = false;

    while (true) {
        while (my_strcmp(argv[*index], "-dump") == 0) {
            *index += 2;
        }
        is_load_address_flag = my_strcmp(argv[*index], "-a") == 0;
        is_prog_number_flag = my_strcmp(argv[*index], "-n") == 0;
        if (!is_load_address_flag && !is_prog_number_flag) {
            break;
        }
        *(params[is_prog_number_flag]) = my_getnbr(argv[*index + 1]);
        *index += 2;
    }
}

/*
@brief
    Loads a binary file using argv (for custom prog_number or load address).
@param
    vm is the Virtual Machine
@param
    argv are the command line arguments
@param
    argc is the number of command line arguments (length of argv)
@param
    index is the index where parsing flags and binary
@returns
    false on error, true otherwise
@note
    The argv syntax MUST be valid when calling this function.
@note
    A modulo MEMORY_SIZE is applied to the load address.
*/
bool binary_argv_load_single_binary
    (vm_t *vm, unsigned argc, char *argv[], unsigned *index)
{
    char *binary_name = NULL;
    vm_address_t load_address = 0;
    vm_address_t prog_number = 0;

    RETURN_VALUE_IF(!vm || !index || *index >= argc, false);
    binary_name = binary_argv_search_filename(argv, *index);
    binary_argv_handle_flags_before_load_binary
        (argv, index, &load_address, &prog_number);
    load_address %= MEMORY_SIZE;
    return binary_load_at(vm, binary_name, load_address);
}
