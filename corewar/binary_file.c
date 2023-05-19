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

STATIC_FUNCTION bool binary_open
    (vm_t *vm, char *binary,
    vm_champion_t *champion, vm_address_t load_address)
{
    static unsigned champion_number = 0;
    const int fd = vm && binary && champion ? open(binary, O_RDONLY) : -1;

    RETURN_VALUE_IF(fd < 0, false);
    *champion = (vm_champion_t) {
        .carry = CARRY_OFF,
        .number = champion_number,
        .filename = binary,
        .pc = 0,
        .registers = { champion_number++ },
        .clock_cycles_to_wait = 0
    };
    read(fd, &vm->memory[load_address], binary_get_size(fd));
    close(fd);
    return true;
}

bool binary_load_at(char *binary, vm_t *vm, vm_address_t load_address)
{
    vm_champion_t new_champion = {};
    bool status = vm && binary;

    status = status && binary_open(vm, binary, &new_champion, load_address);
    RETURN_VALUE_IF(!status, false);
    if (!champion_add(&vm->champions, &new_champion)) {
        return false;
    }
    return true;
}
