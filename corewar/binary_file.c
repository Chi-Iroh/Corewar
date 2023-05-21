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

/*
@brief
    Checks the size of a file.
@param
    fd is the file descriptor returned by an open syscall
@returns
    the size in bytes of the file corresponding to fd.
@note
    fd MUST be a valid file descriptor.
*/
STATIC_FUNCTION size_t binary_get_size(int fd)
{
    const size_t size = lseek(fd, 0, SEEK_END);

    lseek(fd, 0, SEEK_SET);
    return size;
}

/*
@brief

*/
STATIC_FUNCTION bool binary_open
    (vm_t *vm, char *binary,
    vm_champion_t *champion, vm_address_t load_address)
{
    const bool status = vm && binary && champion && load_address < MEMORY_SIZE;
    const int fd = status ? open(binary, O_RDONLY) : -1;

    RETURN_VALUE_IF(fd < 0, false);
    champion->carry = CARRY_OFF;
    champion->filename = binary;
    champion->pc = 0;
    champion->clock_cycles_to_wait = 0;
    champion->load_address = load_address;
    champion->size = binary_get_size(fd);
    read(fd, &vm->memory[load_address], champion->size);
    close(fd);
    return champion->size <= MEMORY_SIZE - load_address;
}

bool binary_load_at(vm_t *vm, char *binary, vm_address_t load_address)
{
    static unsigned n_champions = 0;
    vm_champion_t *new_champion = &vm->champions[n_champions++];
    bool status = vm && binary;

    status = status && binary_open(vm, binary, new_champion, load_address);
    RETURN_VALUE_IF(!status, false);
    return true;
}
