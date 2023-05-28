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
    the size in bytes of the file corresponding to fd (including header).
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
    Checks if a champion's size is valid or not, depending on its load address.
@param
    size is the file size in bytes
@param
    load_address is where to load the champion's code in memory
@returns
    true if file content (without header) fits in memory at given address,
        otherwise false.
*/
STATIC_FUNCTION bool binary_is_size_valid
    (size_t size, vm_address_t load_address)
{
    const vm_address_t memory_free_space = MEMORY_SIZE - load_address;

    RETURN_VALUE_IF(size <= HEADER_LENGTH, false);
    RETURN_VALUE_IF(size - HEADER_LENGTH > memory_free_space, false);
    return true;
}

/*
@brief
    Opens a binary and copies its content in the memory, according to its
        load address.
@param
    vm is the Virtual Machine
@param
    binary is the file name
@param
    champion is champion address (default-initialized)
@param
    load address is the memory address where the champion code will be written
@returns
    true is success, false if failure
@note
    Trying to load a program at a too big address
        (not enough memory to write the champion code) is considered as a
        failure, thus returns false.
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
    champion->cycles_to_wait = 0;
    champion->load_address = load_address;
    champion->size = binary_get_size(fd);

    if (!binary_is_size_valid(champion->size, load_address)) {
        close(fd);
        return false;
    }
    champion->size -= HEADER_LENGTH;
    lseek(fd, HEADER_LENGTH, SEEK_SET);
    read(fd, &vm->memory[load_address], champion->size);
    close(fd);
    return true;
}

/*
@brief
    Loads a binary at a given memory address.
@param
    vm is the Virtual Machine
@param
    binary is the champion filename
@param
    load_address is where to load the code in the memory
@returns
    true on success, false on failure
@note
    A MEMORY_SIZE modulo will be applied to the load address.
*/
bool binary_load_at(vm_t *vm, char *binary,
    vm_address_t load_address, unsigned index)
{
    static unsigned n_champions = 0;
    vm_champion_t *new_champion = NULL;
    bool status = vm && binary;

    if (index == UINT_MAX) {
        new_champion = &vm->champions[n_champions++];
    } else {
        new_champion = &vm->champions[index];
    }
    status = status && binary_open(vm, binary, new_champion, load_address);
    RETURN_VALUE_IF(!status, false);
    return true;
}
