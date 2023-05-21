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

STATIC_FUNCTION void display_help(char *argv[])
{
    RETURN_IF(!argv[1] || argv[2]);
    RETURN_IF(my_strcmp(argv[1], "--help") * my_strcmp(argv[1], "-h") != 0);
    my_puts(
        "USAGE\n"
        "./corewar [-dump nbr_cycle] [[-n prog_number] [-a load_address] "
        "prog_name] ...\n"
        "DESCRIPTION\n"
        "-dump nbr_cycle dumps the memory after the nbr_cycle execution (if "
        "the round isn't already over) with the following format: 32 "
        "bytes/line\n"
        "in hexadecimal (A0BCDEFE1DD3...)\n"
        "-n prog_number sets the next program's number. By default, the first "
        "free number in the parameter order\n"
        "-a load_address sets the next program's loading address. When no "
        "addres is specified, optimize so that the processes are as far away "
        "from each other as possible. The addresses are MEM_SIZE modulo."
    );
    exit(0);
}

int main(int argc, char *argv[])
{
    bool status = true;
    vm_t vm = {};

    display_help(argv);
    status = binary_load_all(&vm, argc, argv);
    printf("%d\n", status);
    for (vm_address_t i = 0; i < vm.n_champions && vm.champions[i].filename; i++) {
        puts(vm.champions[i].filename);
    }
    dump_memory(&vm, 0);
    free(vm.champions);
    return !status * 84;
}
