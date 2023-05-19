/*
** EPITECH PROJECT, 2023
** binary_file.c
** File description:
** -> Binary utilities (open, read...)
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/my_macros.h"
#include "../include/corewar/corewar.h"

STATIC_FUNCTION size_t binary_get_size(int fd)
{
    const size_t size = lseek(fd, 0, SEEK_END);

    lseek(fd, 0, SEEK_SET);
    return size;
}

STATIC_FUNCTION void binary_read(uint8_t *buffer, int fd, size_t size)
{
    if (buffer) {
        read(fd, buffer, size);
    }
}

STATIC_FUNCTION bool binary_open(char *binary, vm_champion_t *champion)
{
    static unsigned champion_number = 0;
    const int fd = binary && champion ? open(binary, O_RDONLY) : -1;

    RETURN_VALUE_IF(fd < 0, false);
    *champion = (vm_champion_t) {
        .carry = CARRY_OFF,
        .number = champion_number,
        .filename = binary,
        .pc = 0,
        .registers = { champion_number++ },
        .code_size = binary_get_size(fd),
        .code = NULL,
        .clock_cycles_to_wait = 0
    };
    champion->code = malloc(sizeof(uint8_t) * champion->code_size);
    binary_read(champion->code, fd, champion->code_size);
    close(fd);
    return champion->code != NULL;
}

bool binary_add(char *binary, vm_t *vm)
{
    vm_champion_t new_champion = {};

    RETURN_VALUE_IF(!vm || !binary, false);
    RETURN_VALUE_IF(!binary_open(binary, &new_champion), NULL);
    if (!champion_add(&vm->champions, &new_champion)) {
        champion_free_struct(&new_champion);
        return false;
    }
    return true;
}
