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
        status &= binary_add(argv[i], &vm);
    }
    printf("%d\n", status);
    while (vm.champions) {
        printf("%s -> %zu bytes\n", vm.champions->filename, vm.champions->code_size);
        for (unsigned i = 0; i < vm.champions->code_size; i++) {
            putchar(vm.champions->code[i]);
        }
        putchar('\n');
        if (!vm.champions->next) {
            break;
        }
        vm.champions = vm.champions->next;
    }
    while (vm.champions && vm.champions->previous) {
        vm.champions = vm.champions->previous;
    }
    main_free(&vm);
    return !status * 84;
}
