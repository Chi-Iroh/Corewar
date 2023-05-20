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
#include "../include/my_macros.h"
#include "../include/corewar/corewar.h"

STATIC_FUNCTION void main_free(vm_t *vm)
{
    RETURN_IF(!vm);
    champions_free(&vm->champions);
}

int main(int argc, char *argv[])
{
    vm_t vm = {
        .champions = NULL,
        .memory = {}
    };
    bool status = true;

    for (unsigned i = 1; i < (unsigned)argc; i++) {
        status &= binary_load_at(argv[i], &vm, 0);
    }
    printf("%d\n", status);
    while (vm.champions) {
        puts(vm.champions->filename);
        if (!vm.champions->next) {
            break;
        }
        vm.champions = vm.champions->next;
    }
    while (vm.champions && vm.champions->previous) {
        vm.champions = vm.champions->previous;
    }
    dump_memory(&vm, 0);
    main_free(&vm);
    return !status * 84;
}
