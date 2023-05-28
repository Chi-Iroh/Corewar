/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** -> Corewar main
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/corewar/corewar.h"

const char *const HELP_MSG =
"USAGE\n"
"./corewar [-dump nbr_cycle] "
"[[-n prog_number] [-a load_address] prog_name] ...\n"
"DESCRIPTION\n"
"-dump nbr_cycle dumps the memory after the nbr_cycle execution "
"(if the round isn't\nalready over) with the following format: 32 bytes/line\n"
"in hexadecimal (A0BCDEFE1DD3...)\n"
"-n prog_number sets the next program's number. "
"By default, the first free number\nin the parameter order\n"
"-a load_address sets the next program's loading address. When no address is\n"
"specified, optimize the addresses so that the processes are as far\n"
"away from each other as possible. The addresses are MEM_SIZE modulo.";

STATIC_FUNCTION void display_help(char *argv[])
{
    RETURN_IF(!argv[1] || argv[2]);
    RETURN_IF(my_strcmp(argv[1], "--help") * my_strcmp(argv[1], "-h") != 0);
    my_puts((char*)HELP_MSG);
    exit(0);
}

int main(int argc, char *argv[])
{
    bool status = true;
    vm_t vm = {};

    display_help(argv);
    status = binary_load_all(&vm, argc, argv);
    if (status) {
        scheduler_execute(&vm);
    }
    free(vm.champions);
    return !status * 84;
}
