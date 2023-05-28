/*
** EPITECH PROJECT, 2023
** binary_file.c
** File description:
** -> Writes ASM file to binary.
*/

#include <unistd.h>
#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/asm/asm.h"

STATIC_FUNCTION char *parser_line_get_header_value
    (parser_line_t *single_line, const char *header_field)
{
    parser_instruction_t *instruction = single_line->instruction;

    while (instruction) {
        if (my_strcmp(instruction->word, header_field) != 0) {
            instruction = instruction->next;
            continue;
        }
        instruction = instruction->next;
        return instruction ? instruction->word : NULL;
    }
    return NULL;
}

STATIC_FUNCTION bool header_get_name_and_comment
    (parser_line_t *file, header_t *header)
{
    char *name = NULL;
    char *comment = NULL;

    while (file) {
        if (!comment) {
            comment = parser_line_get_header_value(file, COMMENT_CMD_STRING);
        }
        if (!name) {
            name = parser_line_get_header_value(file, NAME_CMD_STRING);
        }
        file = file->next;
    }
    RETURN_VALUE_IF(my_strlen(name) > PROG_NAME_LENGTH + 2, false);
    RETURN_VALUE_IF(my_strlen(comment) > COMMENT_LENGTH + 2, false);
    my_strcpy(&header->prog_name[0], &name[1]);
    my_strcpy(&header->comment[0], &comment[1]);
    header->prog_name[my_strlen(&name[1]) - 1] = '\0';
    header->comment[my_strlen(&comment[1]) - 1] = '\0';
    return true;
}

bool binary_write_prog_size(int fd, uint64_t size)
{
    const unsigned size_bytes = PROG_SIZE_SIZE;
    const uint8_t prog_size[PROG_SIZE_SIZE] = {
        [PROG_SIZE_SIZE - 8] = (size & 0xFF'00'00'00'00'00'00'00) >> 56,
        [PROG_SIZE_SIZE - 7] = (size & 0x00'FF'00'00'00'00'00'00) >> 48,
        [PROG_SIZE_SIZE - 6] = (size & 0x00'00'FF'00'00'00'00'00) >> 40,
        [PROG_SIZE_SIZE - 5] = (size & 0x00'00'00'FF'00'00'00'00) >> 32,
        [PROG_SIZE_SIZE - 4] = (size & 0x00'00'00'00'FF'00'00'00) >> 24,
        [PROG_SIZE_SIZE - 3] = (size & 0x00'00'00'00'00'FF'00'00) >> 16,
        [PROG_SIZE_SIZE - 2] = (size & 0x00'00'00'00'00'00'FF'00) >> 8,
        [PROG_SIZE_SIZE - 1] = size & 0x00'00'00'00'00'00'00'FF
    };
    bool status = true;

    status &= lseek(fd, PROG_SIZE_POSITION, SEEK_SET) == PROG_SIZE_POSITION;
    return status && write(fd, &prog_size[0], size_bytes) == size_bytes;
}

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
@note
    Code note : prog name and comment are encoded starting at their second char
        because the first is a double quote from the ASM file.
@note
    0 is written instead of the real prog size because it will be calculated
        later, and insertion isn't possible.
@note
    4 zero-bytes are written after the comment for padding purpose.
*/
bool binary_write_header(int fd, header_t *header)
{
    size_t n_written_bytes = 0;
    static const uint64_t zero = 0;
    static const uint8_t magic[MAGIC_NUMBER_SIZE] = {
        [MAGIC_NUMBER_SIZE - 4] = (COREWAR_EXEC_MAGIC & 0xFF'00'00'00) >> 24,
        [MAGIC_NUMBER_SIZE - 3] = (COREWAR_EXEC_MAGIC & 0x00'FF'00'00) >> 16,
        [MAGIC_NUMBER_SIZE - 2] = (COREWAR_EXEC_MAGIC & 0x00'00'FF'00) >> 8,
        [MAGIC_NUMBER_SIZE - 1] = COREWAR_EXEC_MAGIC & 0x00'00'00'FF
    };

    n_written_bytes += write(fd, &magic[0], MAGIC_NUMBER_SIZE);
    n_written_bytes += write(fd, &header->prog_name[0], PROG_NAME_LENGTH);
    n_written_bytes += write(fd, &zero, PROG_SIZE_SIZE);
    n_written_bytes += write(fd, &header->comment[0], COMMENT_LENGTH);
    n_written_bytes += write(fd, &zero, PADDING_AFTER_COMMENT);
    return n_written_bytes == HEADER_LENGTH;
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
bool binary_write_file
    (int fd, parser_line_t *file, parser_label_t *labels)
{
    parser_line_t *const file_copy = file;
    parser_instruction_t *instruction = NULL;
    header_t header = {};
    bool status = true;

    RETURN_VALUE_IF(fd < 0 || !file, false);
    status &= header_get_name_and_comment(file, &header);
    status &= binary_write_header(fd, &header);
    while (status && file) {
        instruction = file->instruction;
        skip_labels(&instruction);
        if (instruction && parser_is_mnemonic(instruction->word)) {
            status &= binary_write_instruction(fd, instruction, file, labels);
        }
        file = file->next;
    }
    file = file_copy;
    return status && binary_write_prog_size(fd, parser_get_file_size(file));
}
