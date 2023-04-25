/*
** EPITECH PROJECT, 2023
** asm.h
** File description:
** -> Header for assembly part
*/

#pragma once

#include <stdbool.h>
#include <op.h>

typedef struct asm_parser_instruction {
    char *word;
    struct asm_parser_instruction *next;
    struct asm_parser_instruction *previous;
} asm_parser_instruction_t;

typedef struct asm_parser_line {
    asm_parser_instruction_t *instruction;
    struct asm_parser_line *next;
    struct asm_parser_line *previous;
} asm_parser_line_t;

typedef struct {
    asm_parser_line_t *line;
} asm_file_t;

void asm_parser_free_instruction
(asm_parser_instruction_t **instruction);
void asm_parser_free_line(asm_parser_line_t **line);

bool asm_parser_instruction_append_word
(asm_parser_instruction_t *node, char *word);
bool asm_parser_line_append_instruction
(asm_parser_line_t *node, asm_parser_instruction_t *instruction);

bool asm_parser_is_mnemonic(char *word);
bool asm_parser_is_label(char *word);
bool asm_parser_is_direct_value(char *word);
bool asm_parser_is_indirect_value(char *word);
bool asm_parser_is_register(char *word);

#define ASM_PARSER_WORD_TYPES 4

extern bool (*asm_parser_syntax_functions[WORD_TYPE_MAX])(char*);
extern const unsigned asm_parser_word_types[4];
