/*
** EPITECH PROJECT, 2023
** binary.c
** File description:
** -> Writes ASM to binary
*/

#include <stdio.h>
#include "../include/my_macros.h"
#include "../include/asm/asm.h"

/*
@brief
    Writes an ASM header in binary (.cor).
@param
    file is the file to write in
@param
    header is the header information
@returns
    true on success, false on failure
*/
STATIC_FUNCTION bool binary_write_header(FILE *file, header_t *header)
{
    bool status = true;
    uint8_t prog_size[4] = {};
    static const uint8_t magic[4] = {
        (COREWAR_EXEC_MAGIC & 0xFF'00'00'00) >> 24,
        (COREWAR_EXEC_MAGIC & 0x00'FF'00'00) >> 16,
        (COREWAR_EXEC_MAGIC & 0x00'00'FF'00) >> 8,
        COREWAR_EXEC_MAGIC & 0x00'00'00'FF
    };

    RETURN_VALUE_IF(!file || !header, false);
    status &= fseek(file, 0, SEEK_SET);
    prog_size[0] = header->prog_size & 0xFF'00'00'00;
    prog_size[1] = header->prog_size & 0x00'FF'00'00;
    prog_size[2] = header->prog_size & 0x00'00'FF'00;
    prog_size[3] = header->prog_size & 0x00'00'00'FF;
    status &= fwrite(&magic[0], 1, 4, file);
    status &= fwrite(header->prog_name, 1, PROG_NAME_LENGTH, file);
    status &= fwrite(&prog_size[0], 1, 4, file);
    status &= fwrite(&header->comment[0], 1, COMMENT_LENGTH, file);
    return status;
}
