/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** -> Corewar main
*/

#include "../include/corewar/corewar.h"


int main(void)
{
    cpu_t cpu = {
        .memory = {},
        .registers = { 1 },
        .carry = CARRY_OFF
    };

    return 0;
}
