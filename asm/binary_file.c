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
    const uint8_t prog_size[8] = {
        (size & 0xFF'00'00'00'00'00'00'00) >> 56,
        (size & 0x00'FF'00'00'00'00'00'00) >> 48,
        (size & 0x00'00'FF'00'00'00'00'00) >> 40,
        (size & 0x00'00'00'FF'00'00'00'00) >> 32,
        (size & 0x00'00'00'00'FF'00'00'00) >> 24,
        (size & 0x00'00'00'00'00'FF'00'00) >> 16,
        (size & 0x00'00'00'00'00'00'FF'00) >> 8,
        size & 0x00'00'00'00'00'00'00'FF
    };
    bool status = true;

    status &= lseek(fd, PROG_SIZE_POSITION, SEEK_SET) == PROG_SIZE_POSITION;
    return status && write(fd, &prog_size[0], 8) == 8;
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
    static const uint8_t magic[4] = {
        (COREWAR_EXEC_MAGIC & 0xFF'00'00'00) >> 24,
        (COREWAR_EXEC_MAGIC & 0x00'FF'00'00) >> 16,
        (COREWAR_EXEC_MAGIC & 0x00'00'FF'00) >> 8,
        COREWAR_EXEC_MAGIC & 0x00'00'00'FF
    };

    n_written_bytes += write(fd, &magic[0], 4);
    n_written_bytes += write(fd, &header->prog_name[0], PROG_NAME_LENGTH);
    n_written_bytes += write(fd, &zero, 8);
    n_written_bytes += write(fd, &header->comment[0], COMMENT_LENGTH);
    n_written_bytes += write(fd, &zero, 4);
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
bool binary_write_file(int fd, parser_line_t *file_content)
{
    parser_instruction_t *instruction = NULL;
    header_t header = {};
    uint64_t size = 0;
    bool status = true;

    RETURN_VALUE_IF(fd < 0 || !file_content, false);
    status &= header_get_name_and_comment(file_content, &header);
    status &= binary_write_header(fd, &header);
    while (status && file_content) {
        instruction = file_content->instruction;
        while (parser_is_label(instruction->word, LABEL_COLON_END)) {
            instruction = instruction->next;
            BREAK_IF(!instruction);
        }
        if (instruction && parser_is_mnemonic(instruction->word)) {
            status &= binary_write_instruction(fd, instruction, &size);
        }
        file_content = file_content->next;
    }
    return status && binary_write_prog_size(fd, size);
}
