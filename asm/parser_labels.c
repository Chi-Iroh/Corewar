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

/*STATIC_FUNCTION void asm_parser_free_single_instruction
    (asm_parser_instruction_t **instruction, bool free_word)
{
    asm_parser_instruction_t *copy_next = NULL;

    RETURN_IF(!instruction || !(*instruction));
    copy_next = (*instruction)->next;
    if (free_word) {
        FREE_IF_ALLOCATED((*instruction)->word, free);
    }
    free(*instruction);
    *instruction = copy_next;
}*/

STATIC_FUNCTION asm_parser_instruction_t *asm_parser_get_instruction_start
    (asm_parser_instruction_t *instruction, asm_parser_line_t *line)
{
    asm_parser_instruction_t *copy_instruction =
        line ? line->instruction : NULL;

    RETURN_VALUE_IF(!instruction, NULL);
    while (copy_instruction != instruction && copy_instruction) {
        copy_instruction = copy_instruction->next;
    }
    RETURN_VALUE_IF(!copy_instruction, NULL);
    while (line) {
        while (instruction && !asm_parser_is_mnemonic(instruction->word)) {
            instruction = instruction->next;
        }
        line = line->next;
    }
    return instruction ? instruction : NULL;
}

STATIC_FUNCTION bool asm_parser_init_label
    (asm_parser_label_t *node, asm_parser_label_t *previous,
    asm_parser_instruction_t *instruction, asm_parser_line_t *line)
{
    RETURN_VALUE_IF(!node || !instruction || !line, false);
    node->name = my_strdup(instruction->word);
    node->previous = previous;
    node->line = asm_parser_get_instruction_start(instruction, line);
    node->next = NULL;
    return node->name != NULL;
}

STATIC_FUNCTION bool asm_parser_add_label
    (asm_parser_label_t **label, asm_parser_instruction_t **instruction, asm_parser_line_t *line)
{
    asm_parser_label_t *node = label && instruction && *instruction ?
        malloc(sizeof(asm_parser_label_t)) : NULL;

    RETURN_VALUE_IF(!node, false);
    while (*label && (*label)->next) {
        *label = (*label)->next;
    }
    if (!asm_parser_init_label(node, *label, *instruction, line)) {
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

STATIC_FUNCTION bool asm_parse_line_labels
    (asm_parser_line_t **single_line, asm_parser_label_t **label)
{
    bool status = true;
    asm_parser_instruction_t **instruction = NULL;
    asm_parser_instruction_t *copy_next = NULL;

    RETURN_VALUE_IF(!single_line || !(*single_line) || !label, false);
    instruction = &(*single_line)->instruction;
    while (*instruction && status && asm_parser_is_label((*instruction)->word, LABEL_COLON_END)) {
        copy_next = (*instruction)->next;
        status &= asm_parser_add_label(label, instruction, *single_line);
        *instruction = copy_next;
    }
    return status;
}

bool asm_parse_labels(asm_parser_line_t *file, asm_parser_label_t **labels)
{
    bool status = true;
    asm_parser_label_t *labels_node = NULL;

    RETURN_VALUE_IF(!file, NULL);
    while (status && file->next) {
        status &= asm_parse_line_labels(&file, &labels_node);
        file = file->next;
    }
    if (!status) {
        asm_parser_free_labels(&labels_node);
        return false;
    }
    *labels = labels_node;
    return true;
}
