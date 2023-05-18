/*
** EPITECH PROJECT, 2023
** asm_types.h
** File description:
** -> Data structures for ASM.
*/

#pragma once

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

typedef struct asm_parser_label {
    char *name;
    asm_parser_instruction_t *line;
    struct asm_parser_label *next;
    struct asm_parser_label *previous;
} asm_parser_label_t;

extern const asm_parser_instruction_t ASM_PARSER_EMPTY_INSTRUCTION;
extern const asm_parser_line_t ASM_PARSER_EMPTY_LINE;

/*
    Don't change the value of PARSER_ERROR nor PARSER_OK !
    Must match to boolean (0 = error, 1 = ok)
*/
typedef enum {
    PARSER_ERROR = 0,
    PARSER_OK = 1,
    PARSER_COMMENT,
    PARSER_END
} asm_parser_status_t;

typedef enum {
    LABEL_COLON_BEGIN,
    LABEL_COLON_END,
    LABEL_COLON_NONE,
    LABEL_COLON_MAX
} asm_parser_label_colon_pos_t;
