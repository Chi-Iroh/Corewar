/*
** EPITECH PROJECT, 2023
** index_label.c
** File description:
** -> Process labels
*/

#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/asm/asm.h"

STATIC_FUNCTION unsigned single_word_get_size(char *word)
{
    const unsigned op_tab_index = mnemonic_index(word);

    if (parser_is_direct_value(word)) {
        return ARG_SIZE[PARAMETER_DIRECT];
    }
    if (parser_is_indirect_value(word)) {
        return ARG_SIZE[PARAMETER_INDIRECT];
    }
    if (parser_is_register(word)) {
        return ARG_SIZE[PARAMETER_REGISTER];
    }
    return op_tab_index == N_OP ?
        0 : 1 + !MNEMONIC_HAS_NO_CODING_BYTE[op_tab[op_tab_index].opcode];
}

STATIC_FUNCTION bool label_search_forward
    (parser_label_t *single_label, parser_instruction_t *current_instruction,
    parser_line_t *current_line, uint16_t *counter)
{
    parser_instruction_t *const label_location = single_label->line;
    bool has_found = false;

    *counter = 0;
    while (current_line && !has_found) {
        while (current_instruction && !has_found) {
            counter += single_word_get_size(current_instruction->word);
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
    while (current_line && !has_found) {
        while (current_instruction && !has_found) {
            counter += single_word_get_size(current_instruction->word);
            has_found = current_instruction == label_location;
            current_instruction = current_instruction->previous;
        }
        current_line = current_line->previous;
    }
    *counter = 0x01'00'00 - *counter;
    return has_found;
}

STATIC_FUNCTION bool label_to_index
    (parser_label_t *single_label, parser_instruction_t *current_instruction,
    parser_line_t *current_line, uint16_t *index)
{
    return label_search_forward
        (single_label, current_instruction, current_line, index) &&
        label_search_backward
            (single_label, current_instruction, current_line, index);
}

bool find_label
    (parser_label_t *labels, parser_instruction_t *current_instruction,
    parser_line_t *current_line, uint16_t *index)
{
    char *const label_name = current_instruction ?
        &current_instruction->word[2] : NULL;

    RETURN_VALUE_IF
        (!labels || !current_instruction || !current_line || !index, false);
    while (labels && my_strcmp(labels->name, label_name) != 0) {
        labels = labels->next;
    }
    RETURN_VALUE_IF(!labels, false);
    return label_to_index(labels, current_instruction, current_line, index);
}
