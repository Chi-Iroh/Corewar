/*
** EPITECH PROJECT, 2023
** parser.c
** File description:
** -> ASM parser
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/asm/asm.h"

const parser_line_t PARSER_EMPTY_LINE = {
    .instruction = NULL,
    .next = NULL,
    .previous = NULL
};

const parser_instruction_t PARSER_EMPTY_INSTRUCTION = {
    .word = NULL,
    .next = NULL,
    .previous = NULL
};

/*
@brief
    Parses an assembly file WITHOUT CHECKING SYNTAX.
@param
    filename is the path to the target file.
@returns
    NULL on error, otherwise a valid linked list head.
@note
    [CODE] Don't swap the order of str_begin and parser_add_line !
*/
parser_line_t *parse_file(char *filename)
{
    FILE *const file = filename ? fopen(filename, "r") : NULL;
    parser_line_t *code = NULL;
    char *line = NULL;
    size_t n = 0;
    ssize_t read = 0;

    RETURN_VALUE_IF(!file, NULL);
    while ((read = getline(&line, &n, file)) != EOF) {
        if (*str_begin(line) != '#' && !parser_add_line(line, &code)) {
            read = -1;
            break;
        }
    }
    fclose(file);
    if (read == EOF && errno != 0) {
        parser_free_line(&code);
    }
    FREE_IF_ALLOCATED(line, free);
    return code;
}
