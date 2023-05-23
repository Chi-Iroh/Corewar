/*
** EPITECH PROJECT, 2023
** binary_read_write.c
** File description:
** -> Functions to easily read or write values in binary
*/

#include "../include/my_macros.h"
#include "../include/asm/asm.h"

/*
@brief
    Writes a value into an array of bytes.
@param
    value is the value to write
@param
    buffer is where to write
@param
    size is the EXACT size of the buffer in bytes
@attention
    BIG ENDIAN writing
*/
void binary_write(uintmax_t value, uint8_t buffer[], unsigned size)
{
    unsigned n_bits = 0;

    for (unsigned i = 0; i < size; i++) {
        n_bits = (size - i - 1) * 8;
        buffer[i] = (value & (0xFF << n_bits)) >> n_bits;
    }
}

/*
@brief
    Reads a value from an array of bytes.
@param
    buffer is an array containing the value bytes
@param
    value is a pointer to store the read value
@param
    size is the size of the value in bytes
@attention
    BIG ENDIAN reading
@note
    Does nothing if value is a NULL pointer.
*/
void binary_read(uint8_t buffer[], uintmax_t *value, unsigned size)
{
    RETURN_IF(!value);
    *value = 0;
    for (unsigned i = 0; value && i < size; i++) {
        *value <<= 8;
        *value |= buffer[size - i - 1];
    }
}
