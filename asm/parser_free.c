/*
** EPITECH PROJECT, 2023
** parser.c
** File description:
** -> Parser for assembly files
*/

#include <stdlib.h>
#include "../include/my_macros.h"
#include "../include/asm/asm.h"

/*
@brief
    Properly frees an instruction (parser_instruction_t linked list).
    instruction should be the address of an existing instruction linked list.
@note
    If *instruction isn't the first node, goes back to free from the very
    first node.
    If instruction or *instruction is NULL, returns.
*/
void parser_free_instruction(parser_instruction_t **instruction)
{
    parser_instruction_t *copy_next = NULL;

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
    Properly frees a line (parser_line_t linked list).
@param
    line should be the address of an existing line linked list.
@note
    If *line isn't the first node, goes back to free from the very first node.
@note
    If line or *line is NULL, returns.
*/
void parser_free_line(parser_line_t **line)
{
    parser_line_t *copy_next = NULL;

    RETURN_IF(!line || !(*line));
    while ((*line)->previous) {
        *line = (*line)->previous;
    }
    while (*line) {
        copy_next = (*line)->next;
        parser_free_instruction(&(*line)->instruction);
        free(*line);
        *line = copy_next;
    }
}

/*
@brief
    Properly frees labels.
@param
    labels should be the address of an existing bale linked list.
@note
    If *labels isn't the first node, goes back to free
        from the very first node.
@note
    If labels or *labels is NULL, returns;
*/
void parser_free_labels(parser_label_t **labels)
{
    parser_label_t *copy_next = NULL;

    RETURN_IF(!labels || !(*labels));
    while ((*labels)->previous) {
        *labels = (*labels)->previous;
    }
    while (*labels) {
        copy_next = (*labels)->next;
        FREE_IF_ALLOCATED((*labels)->name, free);
        free(*labels);
        *labels = copy_next;
    }
}
