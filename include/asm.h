/*
** EPITECH PROJECT, 2023
** asm.h
** File description:
** -> Header for assembly part
*/

#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "op.h"
#include "asm_config.h"
#include "asm_types.h"

void asm_parser_free_instruction(asm_parser_instruction_t **instruction);
void asm_parser_free_line(asm_parser_line_t **line);
void asm_parser_free_labels(asm_parser_label_t **labels);

bool asm_parser_instruction_append_word
    (asm_parser_instruction_t *node, char *word);
void asm_parser_line_append_instruction
    (asm_parser_instruction_t **node, asm_parser_instruction_t *instruction);
void asm_parser_file_append_line
    (asm_parser_line_t *file, asm_parser_line_t *line);

bool asm_parser_is_mnemonic(char *word);
bool asm_parser_is_label(char *word, asm_parser_label_colon_pos_t color_pos);
bool asm_parser_is_direct_value(char *word);
bool asm_parser_is_indirect_value(char *word);
bool asm_parser_is_register(char *word);

bool asm_parser_add_line(char *line, asm_parser_line_t **file);
bool asm_parser_is_instruction_header(asm_parser_instruction_t *instruction);
void asm_parser_remove_operand_separator(asm_parser_line_t *file);
asm_parser_line_t *asm_parse_file(char *filename);
bool asm_parse_labels(asm_parser_line_t *file, asm_parser_label_t **labels);
bool asm_parser_check_syntax(asm_parser_line_t *file);

/*
@brief
    Number of types (register, label... -> T_REG, T_LAB ...)
@note
    Macro because a const variable cannot be used as a static array length.
@note
    Should be a constexpr unsigned when C23 will be released and
        fully implemented.
*/
#define ASM_PARSER_WORD_TYPES 4

extern bool (*asm_parser_syntax_functions[ARG_TYPE_MAX])(char*);
extern const unsigned asm_parser_word_types[4];
