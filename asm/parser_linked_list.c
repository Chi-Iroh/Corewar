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
    node is the current instructiion node
@param
    word is the string to append to the next node
@note
    Beware to the lifetime of word !
@note
    Should be malloc'd or point to a static variable.
@returns
    false if an error occured or node is NULL
*/
bool asm_parser_instruction_append_word
(asm_parser_instruction_t *node, char *word)
{
    asm_parser_instruction_t *const new_node = node ?
        malloc(sizeof(asm_parser_instruction_t)) : NULL;

    RETURN_VALUE_IF(!new_node, false);
    new_node->next = node->next;
    new_node->previous = node;
    new_node->word = word;
    node->next = new_node;
    return true;
}

/*
@brief
    Appends an instruction to a line linked list.
@param
    node is the current instruction node
@param
    instruction is the instruction to append to the next node
@note
    Beware to the lifetime of instruction !
@note
    Should be malloc'd or point to a static variable.
@note
    Does nothing if instruction or node is NULL
*/
void asm_parser_line_append_instruction
(asm_parser_line_t *node, asm_parser_instruction_t *instruction)
{
    asm_parser_instruction_t *last = node ? node->instruction : NULL;

    RETURN_IF(!node || !instruction);
    while (last && last->next) {
        last = last->next;
    }
    if (last) {
        last->next = instruction;
    } else {
        node->instruction = instruction;
    }
}
