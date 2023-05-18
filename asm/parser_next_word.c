/*
** EPITECH PROJECT, 2023
** parser_next_word.c
** File description:
** -> Extracts the next word of a string, handling doubles quotes,
**      without escape sequences.
*/

#include <stdlib.h>
#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/asm.h"

/*
@brief
    Tries to extract the next word as a quoted expression.
@param
    line is the string to extract from.
@param
    n is used to store the numbers of characters parsed.
@returns
    true if the line is a quote, otherwise false.
@note
    line DOESN'T begin with a space.
*/
STATIC_FUNCTION bool parser_get_next_word_as_quote(char *line, size_t *n)
{
    unsigned n_quotes = 0;

    RETURN_VALUE_IF(!line || *line != '\"', false);
    RETURN_VALUE_IF(str_count(line, '\"') != 2, false);
    while (n_quotes < 2) {
        n_quotes += *line == '\"';
        (*n)++;
        line++;
    }
    return true;
}

/*
@brief
    Extracts the next word of the line.
@param
    line is the line string.
@param
    status is used to store the parser status (comment, end, ok, fail).
@param
    n is used to store the number of characters read.
@param
    instruction is the linked list node to store the next word.
@returns
    false if fails, otherwise true (also check status).
@note
    line DOESN'T begin with a space.
@note
    If the word is a quote, its length is *n - copy_n because n may contain
        a number of spaces already parsed, so it MUSTNT'T be reset to 0 nor
        be ignored.
*/
STATIC_FUNCTION bool parser_get_next_word_impl
    (char *line, parser_status_t *status, size_t *n,
    parser_instruction_t *instruction)
{
    const size_t copy_n = n ? *n : 0;
    char *const space_pos = line ? str_find_pred(line, my_isspace) : NULL;
    char *word = NULL;

    RETURN_VALUE_IF(!line || !status || !n || !instruction, false);
    if (parser_get_next_word_as_quote(line, n)) {
        FREE_IF_ALLOCATED(instruction->word, free);
        instruction->word = my_strndup(line, *n - copy_n);
        return true;
    }
    word = space_pos ? my_strndup(line, space_pos - line) : my_strdup(line);
    *n += space_pos ? (size_t)(space_pos - line) : my_strlen(line);
    if (!word) {
        *status = PARSER_ERROR;
        return false;
    }
    FREE_IF_ALLOCATED(instruction->word, free);
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
STATIC_FUNCTION parser_instruction_t *parser_get_next_word
    (char *line, parser_status_t *status, size_t *n)
{
    parser_instruction_t *instruction = NULL;

    RETURN_VALUE_IF(!line || !status || !n, NULL);
    *n = str_advance_pred(&line, my_isspace);
    *status = line[0] == '#' ? PARSER_COMMENT : PARSER_OK;
    *status = line[0] == '\0' ? PARSER_END : *status;
    RETURN_VALUE_IF(*status != PARSER_OK, NULL);
    instruction = malloc(sizeof(parser_instruction_t));
    *instruction = PARSER_EMPTY_INSTRUCTION;
    *status = (parser_status_t)(instruction != NULL);
    RETURN_VALUE_IF(!(*status), NULL);
    if (!parser_get_next_word_impl(line, status, n, instruction)) {
        parser_free_instruction(&instruction);
        return NULL;
    }
    return instruction;
}

/*
@brief
    Splits a line into a linked list.
@param
    line is the line string
@returns
    NULL if fails, otherwise a valid pointer to a linked list.
*/
STATIC_FUNCTION parser_line_t *parser_split_line(char *line)
{
    parser_line_t *split_line = malloc(sizeof(parser_line_t));
    parser_instruction_t *instruction = NULL;
    parser_status_t parser_status = PARSER_OK;
    size_t n = 0;

    RETURN_VALUE_IF(!split_line, NULL);
    *split_line = PARSER_EMPTY_LINE;
    while (true) {
        instruction = parser_get_next_word(line, &parser_status, &n);
        if (parser_status != PARSER_OK) {
            break;
        }
        parser_line_append_instruction
            (&split_line->instruction, instruction);
        line += n;
    }
    if (parser_status == PARSER_ERROR) {
        parser_free_line(&split_line);
    }
    return split_line;
}

/*
@brief
    Splits a line and adds it to a file linked list.
@param
    line is the string to parse and add.
@param
    file is an address to the file head.
@returns
    false if either line or file is NULL, otherwise true.
@returns
    true if line only contains spaces or tabulations.
*/
bool parser_add_line(char *line, parser_line_t **file)
{
    parser_line_t *parser_line = NULL;

    RETURN_VALUE_IF(!line || !file, false);
    if (!str_find_not_pred(line, my_isspace)) {
        return true;
    }
    parser_line = parser_split_line(line);
    if (!parser_line) {
        return false;
    }
    if (!(*file)) {
        *file = parser_line;
    } else {
        parser_file_append_line(*file, parser_line);
    }
    return true;
}
