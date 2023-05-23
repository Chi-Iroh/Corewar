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
    Writes an ASM header in the binary file (.cor).
@param
    file is the file to write in
@param
    header is the header information
@returns
    true on success, false on failure
@note
    file and must both be valid pointers
*/
STATIC_FUNCTION bool binary_write_header(FILE *file, header_t *header)
{
    size_t n_written_bytes = 0;
    uint8_t prog_size[4] = {};
    static const uint8_t magic[4] = {
        (COREWAR_EXEC_MAGIC & 0xFF'00'00'00) >> 24,
        (COREWAR_EXEC_MAGIC & 0x00'FF'00'00) >> 16,
        (COREWAR_EXEC_MAGIC & 0x00'00'FF'00) >> 8,
        COREWAR_EXEC_MAGIC & 0x00'00'00'FF
    };

    prog_size[0] = (header->prog_size & 0xFF'00'00'00) >> 24;
    prog_size[1] = (header->prog_size & 0x00'FF'00'00) >> 16;
    prog_size[2] = (header->prog_size & 0x00'00'FF'00) >> 8;
    prog_size[3] = header->prog_size & 0x00'00'00'FF;
    n_written_bytes += fwrite(&magic[0], 1, 4, file) == 4;
    n_written_bytes += fwrite(header->prog_name, 1, PROG_NAME_LENGTH, file);
    n_written_bytes += fwrite(&prog_size[0], 1, 4, file) == 4;
    n_written_bytes += fwrite(&header->comment[0], 1, COMMENT_LENGTH, file);
    return n_written_bytes == HEADER_LENGTH;
}

/*
@brief
    Checks an argument type.
@param
    instruction is the instruction node of the argument
        (see attention section)
@attention
    To properly get all the four (or less, see note section) arguments type,
        this function can be called four times with the node of the first
        argument.
@note
    Whatever is its number of parameters, every instruction "virtually"
        has four parameters for implementation purpose, even if less are
        in ASM files.
*/
STATIC_FUNCTION mnemonic_parameter_t instruction_get_arg_type
    (parser_instruction_t *instruction)
{
    static parser_instruction_t *function_last_parameter = NULL;
    static parser_instruction_t *function_last_processed = NULL;

    RETURN_VALUE_IF(!instruction || !instruction->word, PARAMETER_MAX);
    if (function_last_parameter == instruction) {
        function_last_processed = function_last_processed ?
            function_last_processed->next : NULL;
    } else {
        function_last_parameter = instruction;
        function_last_processed = instruction;
    }
    if (parser_is_register(function_last_processed->word)) {
        return PARAMETER_REGISTER;
    } else if (parser_is_direct_value(function_last_processed->word)) {
        return PARAMETER_DIRECT;
    }
    return parser_is_indirect_value(function_last_processed->word) ?
        PARAMETER_INDIRECT : PARAMETER_MAX;
}

/*
@brief
    Writes an instruction in the binary file (.cor).
@param
    file is the binary file
@param
    instruction is the instruction node
@returns
    false if instruction isn't a mnemonic or write error, otherwise true
*/
STATIC_FUNCTION bool binary_write_instruction
    (FILE *file, parser_instruction_t *instruction)
{
    uint8_t opcode = 0x00;
    uint8_t coding_byte = 0x00;
    size_t n_written_bytes = 0;

    for (unsigned i = 0; file && instruction && i < LAST_OP; i++) {
        if (my_strcmp(op_tab[i].mnemonic, instruction->word) == 0) {
            opcode = op_tab[i].opcode;
            break;
        }
    }
    RETURN_VALUE_IF(opcode == 0x00, false);
    instruction = instruction->next;
    for (unsigned i = 0; i < MAX_ARGS_NUMBER; i++) {
        coding_byte <<= 8;
        coding_byte |= ARG_NAME_TO_BITS[instruction_get_arg_type(instruction)];
    }
    n_written_bytes += fwrite(&opcode, 1, 1, file);
    n_written_bytes += fwrite(&coding_byte, 1, 1, file);
    // write arguments (also increment n_written_bytes), handle indexes size !
    return n_written_bytes; // == expected instruction size in binary
}
