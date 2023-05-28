/*
** EPITECH PROJECT, 2023
** index_label.c
** File description:
** -> Process labels
*/

#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/asm/asm.h"

STATIC_FUNCTION bool label_search_forward
    (parser_label_t *single_label, parser_instruction_t *current_instruction,
    parser_line_t *current_line, uint16_t *counter)
{
    parser_instruction_t *const label_location = single_label->line;
    bool has_found = false;

    *counter = 0;
    while (current_line && !has_found) {
        current_instruction = current_line->instruction;
        while (current_instruction && !has_found) {
            *counter += current_instruction->size;
            has_found = current_instruction == label_location;
            current_instruction = current_instruction->next;
        }
        current_line = current_line->next;
    }
    return has_found;
}

STATIC_FUNCTION bool label_search_backward
    (parser_label_t *single_label, parser_instruction_t *current_instruction,
    parser_line_t *current_line, uint16_t *counter)
{
    parser_instruction_t *const label_location = single_label->line;
    bool has_found = false;

    *counter = 0;
    current_line = current_line->previous;
    current_instruction = current_line ? current_line->instruction : NULL;
    DOUBLY_LINKED_LIST_GO_TO_END(current_instruction);
    while (current_line && !has_found) {
        while (current_instruction && !has_found) {
            *counter += current_instruction->size;
            has_found = current_instruction == label_location;
            current_instruction = current_instruction->previous;
        }
        current_line = current_line->previous;
        BREAK_IF(!current_line);
        current_instruction = current_line->instruction;
        DOUBLY_LINKED_LIST_GO_TO_END(current_instruction);
    }
    *counter = 0x01'00'00 - *counter;
    return has_found;
}

STATIC_FUNCTION bool label_to_index
    (parser_label_t *single_label, parser_instruction_t *current_instruction,
    parser_line_t *current_line, uint16_t *index)
{
    return label_search_forward
        (single_label, current_instruction, current_line, index) ||
        label_search_backward
            (single_label, current_instruction, current_line, index);
}

bool find_label
    (parser_label_t *labels, parser_instruction_t *current_instruction,
    parser_line_t *current_line, uint16_t *index)
{
    char *const label_name = current_instruction ?
        &current_instruction->word[2] : NULL;
    const size_t label_length = my_strlen(label_name);

    RETURN_VALUE_IF
        (!labels || !current_instruction || !current_line || !index, false);
    while (labels && my_strncmp(labels->name, label_name, label_length) != 0) {
        labels = labels->next;
    }
    RETURN_VALUE_IF(!labels, false);
    return label_to_index(labels, current_instruction, current_line, index);
}
