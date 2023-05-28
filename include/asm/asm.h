/*
** EPITECH PROJECT, 2023
** asm.h
** File description:
** -> Header for assembly part
*/

#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "../op.h"
#include "asm_config.h"
#include "asm_types.h"

unsigned mnemonic_index(char *mnemonic);

void parser_free_instruction(parser_instruction_t **instruction);
void parser_free_line(parser_line_t **line);
void parser_free_labels(parser_label_t **labels);

bool parser_instruction_append_word
    (parser_instruction_t *node, char *word);
void parser_line_append_instruction
    (parser_instruction_t **node, parser_instruction_t *instruction);
void parser_file_append_line
    (parser_line_t *file, parser_line_t *line);

bool parser_is_mnemonic(char *word);
bool parser_is_label(char *word, parser_label_colon_pos_t color_pos);
bool parser_is_direct_value(char *word);
bool parser_is_indirect_value(char *word);
bool parser_is_register(char *word);

bool parser_add_line(char *line, parser_line_t **file);
bool parser_is_instruction_header(parser_instruction_t *instruction);
void parser_remove_operand_separator(parser_line_t *file);
parser_line_t *parse_file(char *filename);
bool parse_labels(parser_line_t *file, parser_label_t **labels);
bool parser_check_syntax(parser_line_t *file);

/*
@brief
    Number of types
        (register, label... -> PARAMETER_REGISTER, PARAMETER_LABEL...)
@note
    Macro because a const variable cannot be used as a static array length.
@note
    Should be a constexpr unsigned when C23 will be released and
        fully implemented.
*/
#define PARSER_WORD_TYPES 4

void skip_labels(parser_instruction_t **instruction_address);
bool find_label
    (parser_label_t *labels, parser_instruction_t *current_instruction,
    parser_line_t *current_line, uint16_t *index);

void binary_write(uintmax_t value, uint8_t buffer[], unsigned size);
void binary_read(uint8_t buffer[], uintmax_t *value, unsigned size);
bool binary_write_header(int fd, header_t *header);
uint64_t binary_write_instruction
    (int fd, parser_instruction_t *instruction,
    parser_line_t *line, parser_label_t *labels);
bool binary_write_file
    (int fd, parser_line_t *file_content, parser_label_t *labels);

extern bool (*parser_syntax_functions[PARAMETER_MAX])(char*);
extern const unsigned parser_word_types[4];
