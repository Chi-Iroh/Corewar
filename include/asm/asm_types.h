/*
** EPITECH PROJECT, 2023
** asm_types.h
** File description:
** -> Data structures for ASM.
*/

#pragma once

typedef struct parser_instruction {
    char *word;
    unsigned size;
    struct parser_instruction *next;
    struct parser_instruction *previous;
} parser_instruction_t;

typedef struct parser_line {
    parser_instruction_t *instruction;
    struct parser_line *next;
    struct parser_line *previous;
} parser_line_t;

typedef struct parser_label {
    char *name;
    parser_instruction_t *line;
    struct parser_label *next;
    struct parser_label *previous;
} parser_label_t;

extern const parser_instruction_t PARSER_EMPTY_INSTRUCTION;
extern const parser_line_t PARSER_EMPTY_LINE;

/*
    Don't change the value of PARSER_ERROR nor PARSER_OK !
    Must match to boolean (0 = error, 1 = ok)
*/
typedef enum {
    PARSER_ERROR = 0,
    PARSER_OK = 1,
    PARSER_COMMENT,
    PARSER_END
} parser_status_t;

typedef enum {
    LABEL_COLON_BEGIN,
    LABEL_COLON_END,
    LABEL_COLON_NONE,
    LABEL_COLON_MAX
} parser_label_colon_pos_t;
