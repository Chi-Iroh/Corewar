/*
** EPITECH PROJECT, 2023
** parser_label.c
** File description:
** -> Labels handling
*/

#include <stdlib.h>
#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/asm/asm.h"

/*
@brief
    Searches a label's closest mnemonic to know where does the label redirects.
@param
    label is the label node
@param
    line is the line where is the label
@returns
    NULL is the label isn't in the given line or it is at the end of the file,
        otherwise the node of its instruction.
*/
STATIC_FUNCTION parser_instruction_t *parser_label_get_start
    (parser_instruction_t *label, parser_line_t *line)
{
    parser_instruction_t *copy_label =
        line ? line->instruction : NULL;

    RETURN_VALUE_IF(!label || !line, NULL);
    while (copy_label != label && copy_label) {
        copy_label = copy_label->next;
    }
    RETURN_VALUE_IF(!copy_label, NULL);
    while (line) {
        while (label && !parser_is_mnemonic(label->word)) {
            label = label->next;
        }
        line = line->next;
    }
    return label;
}

/*
@brief
    Initialized a label node.
@param
    node is the node to initialize
@param
    previous is the previous label node
@param
    instruction is the instruction right after the label
@param
    line is the line containing instruction
@returns
    true on success, false on failure
*/
STATIC_FUNCTION bool parser_init_label
    (parser_label_t *node, parser_label_t *previous,
    parser_instruction_t *instruction, parser_line_t *line)
{
    RETURN_VALUE_IF(!node || !instruction || !line, false);
    node->name = my_strdup(instruction->word);
    node->previous = previous;
    node->line = parser_label_get_start(instruction, line);
    node->next = NULL;
    return node->name != NULL;
}

/*
@brief
    Adds a label at the end of the linked list.
@param
    label is the node to add at the end
@param
    instruction is the address of the linked list
@param
    line is the line containing the label
@returns
    true on success, false on failure
*/
STATIC_FUNCTION bool parser_add_label
    (parser_label_t **label, parser_instruction_t *instruction,
    parser_line_t *line)
{
    parser_label_t *node = label && instruction ?
        malloc(sizeof(parser_label_t)) : NULL;

    RETURN_VALUE_IF(!node, false);
    while (*label && (*label)->next) {
        *label = (*label)->next;
    }
    if (!parser_init_label(node, *label, instruction, line)) {
        free(node);
        return false;
    }
    node->line = instruction;
    if (!(*label)) {
        *label = node;
    } else {
        (*label)->next = node;
    }
    return true;
}

/*
@brief
    Parses all the labels of a line.
@param
    single_line is the address of the line to parse
@param
    labels is the address of the labels linked list
@returns
    true on success, false on failure
*/
STATIC_FUNCTION bool parse_line_labels
    (parser_line_t **single_line, parser_label_t **labels)
{
    bool status = true;
    parser_instruction_t *instruction = NULL;

    RETURN_VALUE_IF(!single_line || !(*single_line) || !labels, false);
    instruction = (*single_line)->instruction;
    while (instruction && status) {
        BREAK_IF(!parser_is_label(instruction->word, LABEL_COLON_END));
        status &= parser_add_label(labels, instruction, *single_line);
        instruction = instruction->next;
    }
    return status;
}

/*
@brief
    Parses all the labels of a file.
@param
    file is the file's content
@param
    labels is the address of the label linked list
@returns
    true on success, false on failure
*/
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
