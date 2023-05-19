/*
** EPITECH PROJECT, 2023
** my_memcpy.c
** File description:
** -> Copy raw memory
*/

#include <stddef.h>
#include <stdint.h>

void my_memcpy(void *destination, void *source, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        *((uint8_t*)destination + i) = *((uint8_t*)source + i);
    }
}
