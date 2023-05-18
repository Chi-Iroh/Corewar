/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** -> Corewar main
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/my_macros.h"
#include "../include/corewar/corewar.h"

STATIC_FUNCTION bool binary_open(char *binary, vm_champion_t *champion)
{
    static unsigned champion_number = 0;
    FILE *const file = binary && champion ? fopen(binary, "rb") : NULL;

    RETURN_VALUE_IF(!file, false);
    *champion = (vm_champion_t) {
        .carry = CARRY_OFF,
        .number = champion_number,
        .code = file,
        .pc = 0,
        .registers = { champion_number }
    };
    champion_number++;
    return true;
}

STATIC_FUNCTION bool binary_add(char *binary, vm_t *vm)
{
    vm_champion_t new_champion = {};

    RETURN_VALUE_IF(!vm || !binary, false);
    RETURN_VALUE_IF(!binary_open(binary, &new_champion), NULL);
    if (!champion_add(&vm->champions, &new_champion)) {
        champion_free(&new_champion);
        return false;
    }
    return true;
}

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
        puts(argv[i]);
        status &= binary_add(argv[i], &vm);
    }
    printf("%d\n", status);
    main_free(&vm);
    return !status * 84;
}
