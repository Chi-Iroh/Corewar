/*
** EPITECH PROJECT, 2023
** parser.c
** File description:
** -> ASM parser
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/asm.h"

const asm_parser_line_t ASM_PARSER_EMPTY_LINE = {
    .instruction = NULL,
    .next = NULL,
    .previous = NULL
};

STATIC_FUNCTION bool asm_parser_get_next_word_impl
    (char *line, asm_parser_status_t *status, size_t *n,
    asm_parser_instruction_t *instruction)
{
    char *const space_pos = line ? str_find_pred(line, my_isspace) : NULL;
    char *word = NULL;

    RETURN_VALUE_IF(!line || !status || !n || !instruction, false);
    if (!space_pos) {
        word = my_strdup(line);
        *n += my_strlen(line);
    } else {
        word = my_strndup(line, space_pos - line);
        *n += space_pos - line;
    }
    if (!word) {
        *status = PARSER_ERROR;
        return false;
    }
    instruction->word = word;
    return true;
}

/*
@brief
    Extracts the next word (non-space characters).
@param
    line is the ASM code line to parse.
@param
    status is used to store whether or not the operation succeeded.
    Checking if NULL is returned isn't sufficient, as it is also returned
    when the string only contains spaces or \0.
@param
    n is used to store the amount of characters parsed (including spaces).
@returns
    a pointer to an instruction node.
*/
STATIC_FUNCTION asm_parser_instruction_t *asm_parser_get_next_word
    (char *line, asm_parser_status_t *status, size_t *n)
{
    asm_parser_instruction_t *instruction = NULL;

    RETURN_VALUE_IF(!line || !status || !n, NULL);
    *n = str_advance_pred(&line, my_isspace);
    *status = line[0] == '#' ? PARSER_COMMENT : PARSER_OK;
    *status = line[0] == '\0' ? PARSER_END : *status;
    RETURN_VALUE_IF(*status == PARSER_COMMENT || *status == PARSER_END, NULL);
    instruction = malloc(sizeof(asm_parser_instruction_t));
    *instruction = (asm_parser_instruction_t) {
        .previous = NULL,
        .next = NULL,
        .word = NULL
    };
    *status = (asm_parser_status_t)(instruction != NULL);
    RETURN_VALUE_IF(!(*status), NULL);
    if (!asm_parser_get_next_word_impl(line, status, n, instruction)) {
        asm_parser_free_instruction(&instruction);
        return NULL;
    }
    return instruction;
}

asm_parser_line_t *asm_parser_split_line(char *line)
{
    asm_parser_line_t *split_line = malloc(sizeof(asm_parser_line_t));
    asm_parser_instruction_t *instruction = NULL;
    bool status = split_line != NULL;
    asm_parser_status_t parser_status = PARSER_OK;
    size_t n = 0;

    RETURN_VALUE_IF(!status, NULL);
    *split_line = ASM_PARSER_EMPTY_LINE;
    while (true) {
        instruction = asm_parser_get_next_word(line, &parser_status, &n);
        if (parser_status != PARSER_OK) {
            break;
        }
        asm_parser_line_append_instruction(split_line, instruction);
        line += n;
    }
    if (parser_status == PARSER_ERROR) {
        asm_parser_free_line(&split_line);
    }
    return split_line;
}
