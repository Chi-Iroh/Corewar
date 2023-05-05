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
#include "../include/asm.h"

const asm_parser_line_t ASM_PARSER_EMPTY_LINE = {
    .instruction = NULL,
    .next = NULL,
    .previous = NULL
};

const asm_parser_instruction_t ASM_PARSER_EMPTY_INSTRUCTION = {
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
@attention
    [CODE] Don't swap the order of str_begin and asm_parser_add_line !
*/
asm_parser_line_t *asm_parse_file(char *filename)
{
    FILE *const file = filename ? fopen(filename, "r") : NULL;
    asm_parser_line_t *code = NULL;
    char *line = NULL;
    size_t n = 0;
    ssize_t read = 0;

    RETURN_VALUE_IF(!file, NULL);
    while ((read = getline(&line, &n, file)) != EOF) {
        if (*str_begin(line) != '#' && !asm_parser_add_line(line, &code)) {
            read = -1;
            break;
        }
    }
    fclose(file);
    if (read == EOF && errno != 0) {
        asm_parser_free_line(&code);
    }
    FREE_IF_ALLOCATED(line, free);
    return code;
}
