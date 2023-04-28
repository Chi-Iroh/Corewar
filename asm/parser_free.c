/*
** EPITECH PROJECT, 2023
** parser.c
** File description:
** -> Parser for assembly files
*/

#include <stdlib.h>
#include "../include/my_macros.h"
#include "../include/asm.h"

/*
@brief
    Properly frees an instruction (asm_parser_instruction_t linked list).
    instruction should be the address of an existing instruction linked list.
@note
    If *instruction isn't the first node, goes back to free from the very
    first node.
    If instruction or *instruction is NULL, returns.
*/
void asm_parser_free_instruction(asm_parser_instruction_t **instruction)
{
    asm_parser_instruction_t *copy_next = NULL;

    RETURN_IF(!instruction || !(*instruction));
    while ((*instruction)->previous) {
        *instruction = (*instruction)->previous;
    }
    while (*instruction) {
        copy_next = (*instruction)->next;
        FREE_IF_ALLOCATED((*instruction)->word, free);
        free(*instruction);
        *instruction = copy_next;
    }
}

/*
@brief
    Properly frees a line (asm_parser_line_t linked list).
    line should be the address of an existing line linked list.
@note
    If *line isn't the first node, goes back to free from the very first node.
    If line or *line is NULL, retruns.
*/
void asm_parser_free_line(asm_parser_line_t **line)
{
    asm_parser_line_t *copy_next = NULL;

    RETURN_IF(!line || !(*line));
    while ((*line)->previous) {
        *line = (*line)->previous;
    }
    while (*line) {
        copy_next = (*line)->next;
        asm_parser_free_instruction(&(*line)->instruction);
        free(*line);
        *line = copy_next;
    }
}
