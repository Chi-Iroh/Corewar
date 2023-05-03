/*
** EPITECH PROJECT, 2023
** parser_linked_list.c
** File description:
** -> Linked list management functions for asm parser.
*/

#include <stdlib.h>
#include "../include/my_macros.h"
#include "../include/asm.h"

/*
@brief
    Appends a word to an instruction linked list.
@param
    node is the current instruction node.
@param
    word is the string to append at the end.
@note
    Beware to the lifetime of word !
@note
    word should be malloc'd or point to a static variable.
@returns
    false if an error occured or node is NULL.
*/
bool asm_parser_instruction_append_word
    (asm_parser_instruction_t *node, char *word)
{
    asm_parser_instruction_t *const new_node = node ?
        malloc(sizeof(asm_parser_instruction_t)) : NULL;

    RETURN_VALUE_IF(!new_node, false);
    while (node->next) {
        node = node->next;
    }
    node->next = new_node;
    new_node->next = NULL;
    new_node->previous = node;
    new_node->word = word;
    return true;
}

/*
@brief
    Appends an instruction to a line linked list.
@param
    node is the address of the current instruction node.
@param
    instruction is the instruction to append at the end.
@note
    if *node is NULL, *node is set to instruction.
@note
    Beware to the lifetime of instruction !
@note
    instruction should be malloc'd or point to a static variable.
@note
    Does nothing if instruction or node is NULL.
*/
void asm_parser_line_append_instruction
    (asm_parser_instruction_t **node, asm_parser_instruction_t *instruction)
{
    asm_parser_instruction_t *end = node ? *node : NULL;

    RETURN_IF(!node || !instruction);
    if (!(*node)) {
        *node = instruction;
        return;
    } else {
        while (end->next) {
            end = end->next;
        }
    }
    instruction->previous = end;
    instruction->next = NULL;
    end->next = instruction;
}

/*
@brief
    Appends a line to a file linked list.
@param
    file is the current node.
@param
    line is the line to append at the end.
@note
    Beware to the lifetime of line !
@note
    line should be malloc'd or point to a static variable.
@note
    Does nothing if file or line is NULL.
*/
void asm_parser_file_append_line
    (asm_parser_line_t *file, asm_parser_line_t *line)
{
    RETURN_IF(!file || !line);
    while (file->next) {
        file = file->next;
    }
    line->previous = file;
    line->next = NULL;
    file->next = line;
}
