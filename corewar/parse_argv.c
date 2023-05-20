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

STATIC_FUNCTION bool parse_argv_dump
    (vm_t *vm, char *argv[], unsigned argc, unsigned index)
{
    RETURN_VALUE_IF(!vm || index >= argc - 1, false);
    RETURN_VALUE_IF(my_strcmp(argv[index], "-dump") != 0, false);
    RETURN_VALUE_IF(!argv[index++], false);
    RETURN_VALUE_IF(str_find_not_pred(argv[index], my_isdigit) != NULL, false);
    vm->must_dump_memory = true;
    vm->cycles_before_memory_dump = my_getnbr(argv[index]);
    return true;
}

STATIC_FUNCTION bool parse_argv_prog_number
    (vm_t *vm, char *argv[], unsigned argc, unsigned index)
{
    RETURN_VALUE_IF(!vm || index >= argc - 1, false);
    RETURN_VALUE_IF(my_strcmp(argv[index], "-n") != 0, false);
    RETURN_VALUE_IF(!argv[index++], false);
    RETURN_VALUE_IF(str_find_not_pred(argv[index], my_isdigit) != NULL, false);
    RETURN_VALUE_IF(!argv[++index], false);
    return true;
}

STATIC_FUNCTION bool parse_argv_load_address
    (vm_t *vm, char *argv[], unsigned argc, unsigned index)
{
    RETURN_VALUE_IF(!vm || index >= argc - 1, false);
    RETURN_VALUE_IF(my_strcmp(argv[index], "-a") != 0, false);
    RETURN_VALUE_IF(!argv[index++], false);
    RETURN_VALUE_IF(str_find_not_pred(argv[index], my_isdigit) != NULL, false);
    RETURN_VALUE_IF(!argv[++index], false);
    return true;
}

STATIC_FUNCTION bool parse_argv_is_flag(char *str)
{
    return my_strcmp(str, "-a") == 0 ||
        my_strcmp(str, "-n")  == 0 ||
        my_strcmp(str, "-dump") == 0;
}

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
        status = parse_argv_dump(vm, argv, argc, i);
        status &= parse_argv_prog_number(vm, argv, argc, i);
        status &= parse_argv_load_address(vm, argv, argc, i);
        if (!status) {
            exit(84);
        }
        i += 2;
    }
}
