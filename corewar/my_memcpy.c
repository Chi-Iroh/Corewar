/*
** EPITECH PROJECT, 2023
** my_memcpy.c
** File description:
** -> Copy raw memory
*/

#include <stddef.h>
#include <stdint.h>

/*
@brief
    Same as libc memcpy, copies raw data from a memory location to another.
@param
    destination is where to copy the data
@param
    source is where is read the data
@param
    size is the number of bytes to copy
@note
    No check on address can be performed in this function, be sure the pointers
        are valid and the size won't overflow, otherwise it will lead to
        undefined behaviour.
*/
void my_memcpy(void *destination, void *source, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        *((uint8_t*)destination + i) = *((uint8_t*)source + i);
    }
}
