/*
** EPITECH PROJECT, 2023
** binary_instruction.c
** File description:
** -> Returns the binary code of an instruction
*/

#include <unistd.h>
#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/asm/asm.h"

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
@note
    When instruction is NULL, resets the internal instruction state
        (not to continue to the next node) and then returns PARAMETER_MAX.
*/
STATIC_FUNCTION mnemonic_parameter_t
    instruction_get_arg_type(parser_instruction_t *instruction)
{
    static parser_instruction_t *last_parameter = NULL;
    static parser_instruction_t *last_processed = NULL;

    if (!instruction)
        last_parameter = NULL;
    RETURN_VALUE_IF(!instruction || !instruction->word, PARAMETER_MAX);
    if (last_parameter == instruction) {
        last_processed = last_processed ? last_processed->next : NULL;
        RETURN_VALUE_IF(!last_processed, PARAMETER_MAX);
        RETURN_VALUE_IF(!last_processed->word, PARAMETER_MAX);
    } else {
        last_parameter = instruction;
        last_processed = instruction;
    }
    if (parser_is_register(last_processed->word))
        return PARAMETER_REGISTER;
    else if (parser_is_direct_value(last_processed->word))
        return PARAMETER_DIRECT;
    return parser_is_indirect_value(last_processed->word) ?
        PARAMETER_INDIRECT : PARAMETER_MAX;
}

/*
@brief
    Writes the opcode and coding byte to the binary file.
@param
    file is the binary file
@param
    opcode is the opcode of the instruction
@param
    coding_byte is the coding byte of the instruction
@returns
    true on success, false on failure
*/
STATIC_FUNCTION bool binary_write_instruction_info(int fd,
    uint8_t opcode, uint8_t coding_byte, size_t *prog_size)
{
    const ssize_t expected_written_bytes =
        1 + !MNEMONIC_HAS_NO_CODING_BYTE[opcode];
    ssize_t n_written_bytes = write(fd, &opcode, 1);

    if (!MNEMONIC_HAS_NO_CODING_BYTE[opcode]) {
        n_written_bytes += write(fd, &coding_byte, 1);
    }
    RETURN_VALUE_IF(n_written_bytes != expected_written_bytes, false);
    *prog_size += n_written_bytes;
    return true;
}

STATIC_FUNCTION uintmax_t convert_arg_to_number
    (parser_instruction_t *instruction)
{
    static parser_instruction_t *last_parameter = NULL;
    static parser_instruction_t *last_processed = NULL;

    RETURN_VALUE_IF(!instruction || !instruction->word, 0);
    if (last_parameter == instruction) {
        last_processed = last_processed ? last_processed->next : NULL;
        RETURN_VALUE_IF(!last_processed, 0);
        RETURN_VALUE_IF(!last_processed->word, 0);
    } else {
        last_parameter = instruction;
        last_processed = instruction;
    }
    if (parser_is_register(last_processed->word)) {
        return my_getnbr(&last_processed->word[1]);
    } else if (!parser_is_label(&last_processed->word[1], LABEL_COLON_BEGIN)) {
        return my_getnbr(last_processed->word);
    }
    return 0;
}

/*
@brief
    Writes the arguments of the instruction to the binary file.
@param
    file is the binary file
@param
    instruction is the instruction node
@param
    opcode is the opcode of the instruction
@returns
    true on success, false on failure
*/
STATIC_FUNCTION bool binary_write_arguments(int fd,
    parser_instruction_t *instruction, uint8_t opcode, size_t *prog_size)
{
    uintmax_t arg = 0;
    unsigned arg_size = 0;
    uint8_t arg_1byte = 0;
    uint8_t arg_2bytes[2] = {};
    uint8_t arg_4bytes[4] = {};
    uint8_t *args[] = {
        [1] = &arg_1byte, [2] = &arg_2bytes[0], [4] = &arg_4bytes[0]
    };

    instruction_get_arg_type(NULL);
    convert_arg_to_number(NULL);
    for (unsigned i = 0; i < MAX_ARGS_NUMBER; i++) {
        arg = convert_arg_to_number(instruction);
        arg_size = ARG_SIZE[instruction_get_arg_type(instruction)];
        binary_write(arg, args[arg_size], arg_size);
        RETURN_VALUE_IF(write(fd, args[arg_size], arg_size) != arg_size, false)
        *prog_size += arg_size;
    }
    return true;
}

/*
@brief
    Writes an instruction to the binary file (.cor).
@param
    file is the binary file
@param
    instruction is the instruction node
@returns
    false if instruction isn't a mnemonic or write error, otherwise true
*/
bool binary_write_instruction
    (int fd, parser_instruction_t *instruction, uint64_t *prog_size)
{
    const unsigned index = op_tab_mnemonic_index(instruction->word);
    uint8_t opcode = index == N_OP ? 0x00 : op_tab[index].opcode;
    uint8_t coding_byte = 0x00;
    bool is_ok = true;

    RETURN_VALUE_IF(opcode == 0x00, false);
    instruction = instruction->next;
    RETURN_VALUE_IF(!instruction, false);
    instruction_get_arg_type(NULL);
    for (unsigned i = 0; i < MAX_ARGS_NUMBER; i++) {
        coding_byte <<= 2;
        coding_byte |= ARG_NAME_TO_BITS[instruction_get_arg_type(instruction)];
    }
    is_ok &= binary_write_instruction_info(fd, opcode, coding_byte, prog_size);
    return is_ok && binary_write_arguments(fd, instruction, opcode, prog_size);
}
