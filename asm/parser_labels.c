/*
** EPITECH PROJECT, 2023
** parser_label.c
** File description:
** -> Labels handling
*/

#include <stdlib.h>
#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/asm.h"

/*STATIC_FUNCTION void parser_free_single_instruction
    (parser_instruction_t **instruction, bool free_word)
{
    parser_instruction_t *copy_next = NULL;

    RETURN_IF(!instruction || !(*instruction));
    copy_next = (*instruction)->next;
    if (free_word) {
        FREE_IF_ALLOCATED((*instruction)->word, free);
    }
    free(*instruction);
    *instruction = copy_next;
}*/

STATIC_FUNCTION parser_instruction_t *parser_get_instruction_start
    (parser_instruction_t *instruction, parser_line_t *line)
{
    parser_instruction_t *copy_instruction =
        line ? line->instruction : NULL;

    RETURN_VALUE_IF(!instruction, NULL);
    while (copy_instruction != instruction && copy_instruction) {
        copy_instruction = copy_instruction->next;
    }
    RETURN_VALUE_IF(!copy_instruction, NULL);
    while (line) {
        while (instruction && !parser_is_mnemonic(instruction->word)) {
            instruction = instruction->next;
        }
        line = line->next;
    }
    return instruction ? instruction : NULL;
}

STATIC_FUNCTION bool parser_init_label
    (parser_label_t *node, parser_label_t *previous,
    parser_instruction_t *instruction, parser_line_t *line)
{
    RETURN_VALUE_IF(!node || !instruction || !line, false);
    node->name = my_strdup(instruction->word);
    node->previous = previous;
    node->line = parser_get_instruction_start(instruction, line);
    node->next = NULL;
    return node->name != NULL;
}

STATIC_FUNCTION bool parser_add_label
    (parser_label_t **label, parser_instruction_t **instruction,
    parser_line_t *line)
{
    parser_label_t *node = label && instruction && *instruction ?
        malloc(sizeof(parser_label_t)) : NULL;

    RETURN_VALUE_IF(!node, false);
    while (*label && (*label)->next) {
        *label = (*label)->next;
    }
    if (!parser_init_label(node, *label, *instruction, line)) {
        free(node);
        return false;
    }
    if (!(*label)) {
        *label = node;
    } else {
        (*label)->next = node;
    }
    return true;
}

STATIC_FUNCTION bool parse_line_labels
    (parser_line_t **single_line, parser_label_t **label)
{
    bool status = true;
    parser_instruction_t **instruction = NULL;
    parser_instruction_t *copy_next = NULL;

    RETURN_VALUE_IF(!single_line || !(*single_line) || !label, false);
    instruction = &(*single_line)->instruction;
    while (*instruction && status &&
        parser_is_label((*instruction)->word, LABEL_COLON_END)) {
        copy_next = (*instruction)->next;
        status &= parser_add_label(label, instruction, *single_line);
        *instruction = copy_next;
    }
    return status;
}

bool parse_labels(parser_line_t *file, parser_label_t **labels)
{
    bool status = true;
    parser_label_t *labels_node = NULL;

    RETURN_VALUE_IF(!file, NULL);
    while (status && file->next) {
        status &= parse_line_labels(&file, &labels_node);
        file = file->next;
    }
    if (!status) {
        parser_free_labels(&labels_node);
        return false;
    }
    *labels = labels_node;
    return true;
}
