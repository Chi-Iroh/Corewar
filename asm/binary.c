/*
** EPITECH PROJECT, 2023
** binary.c
** File description:
** -> Writes ASM to binary
*/

#include <stdio.h>
#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/asm/asm.h"

/*
@brief
    Writes all instructions in the binary file (.cor).
@param
    file is the binary file
@param
    instructions is the list of instructions
@returns
    false if write error, otherwise true
*/
STATIC_FUNCTION bool binary_write_instructions(FILE *file,
parser_line_t *instructions)
{
    while (instructions->instruction) {
        if (!binary_write_instruction(file, instructions->instruction))
            return false;
        instructions->instruction = instructions->instruction->next;
    }

    return true;
}

/*
@brief
    Writes an ASM file in the binary file (.cor).
@param
    file is the binary file
@param
    parser is the parser structure
@returns
    false if write error, otherwise true
*/
bool binary_write_file(FILE *file, parser_line_t *binary, header_t *header)
{
    if (!file || !binary)
        return false;
    if (!binary_write_header(file, header))
        return false;
    if (!binary_write_instructions(file, binary))
        return false;

    return true;
}
