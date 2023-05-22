/*
** EPITECH PROJECT, 2023
** parse_argv.c
** File description:
** -> Flag parsing for argv
*/

#include <stdlib.h>
#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/corewar/corewar.h"

/*
@brief
    Parses -dump flag in argv.
@param
    vm is the Virtual Machine.
@param
    argc is the number of command-line arguments
@param
    argv are the command-line arguments
@param
    index is the index where beginning to search
@returns
    true if there's a valid -dump flag at the given index
*/
STATIC_FUNCTION bool parse_argv_dump
    (vm_t *vm, unsigned argc, char *argv[], unsigned index)
{
    RETURN_VALUE_IF(!vm || index >= argc - 1, false);
    RETURN_VALUE_IF(my_strcmp(argv[index], "-dump") != 0, false);
    RETURN_VALUE_IF(!argv[index++], false);
    RETURN_VALUE_IF(str_find_not_pred(argv[index], my_isdigit) != NULL, false);
    vm->must_dump_memory = true;
    vm->cycles_before_memory_dump = my_getnbr(argv[index]);
    return true;
}

/*
@brief
    Parses -n flag in argv.
@param
    vm is the Virtual Machine.
@param
    argc is the number of command-line arguments
@param
    argv are the command-line arguments
@param
    index is the index where beginning to search
@retruns
    true if there's a valid -n flag at the given index
*/
STATIC_FUNCTION bool parse_argv_prog_number
    (vm_t *vm, unsigned argc, char *argv[], unsigned index)
{
    RETURN_VALUE_IF(!vm || index >= argc - 1, false);
    RETURN_VALUE_IF(my_strcmp(argv[index], "-n") != 0, false);
    RETURN_VALUE_IF(!argv[index++], false);
    RETURN_VALUE_IF(str_find_not_pred(argv[index], my_isdigit) != NULL, false);
    RETURN_VALUE_IF(!argv[++index], false);
    return true;
}

/*
@brief
    Parses -a flag in argv.
@param
    vm is the Virtual Machine.
@param
    argc is the number of command-line arguments
@param
    argv are the command-line arguments
@param
    index is the index where beginning to search
@retruns
    true if there's a valid -a flag at the given index
*/
STATIC_FUNCTION bool parse_argv_load_address
    (vm_t *vm, unsigned argc, char *argv[], unsigned index)
{
    RETURN_VALUE_IF(!vm || index >= argc - 1, false);
    RETURN_VALUE_IF(my_strcmp(argv[index], "-a") != 0, false);
    RETURN_VALUE_IF(!argv[index++], false);
    RETURN_VALUE_IF(str_find_not_pred(argv[index], my_isdigit) != NULL, false);
    RETURN_VALUE_IF(!argv[++index], false);
    return true;
}

/*
@brief
    Checks if a string is a commend-line flag or not.
@param
    str is the string to check
@returns
    true if str is either -a, -n or -dump, otherwise false
*/
bool parse_argv_is_flag(char *str)
{
    return my_strcmp(str, "-a") == 0 ||
        my_strcmp(str, "-n") == 0 ||
        my_strcmp(str, "-dump") == 0;
}

/*
@brief
    Parses command-line arguments and exits when no arg or error.
@param
    vm is the Virtual Machine
@param
    argc is the number of command-line arguments
@param
    argv are the command-line arguments
*/
void parse_argv(vm_t *vm, unsigned argc, char *argv[])
{
    bool status = true;

    if (argc == 1) {
        exit(0);
    }
    for (unsigned i = 1; i < argc; ) {
        if (!parse_argv_is_flag(argv[i])) {
            i++;
            continue;
        }
        status = parse_argv_dump(vm, argc, argv, i);
        status |= parse_argv_prog_number(vm, argc, argv, i);
        status |= parse_argv_load_address(vm, argc, argv, i);
        if (!status) {
            exit(84);
        }
        i += 2;
    }
}
