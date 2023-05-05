/*
** EPITECH PROJECT, 2023
** parser_check_header.c
** File description:
** -> Checks for header instructions.
*/

#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/asm.h"

STATIC_FUNCTION bool asm_parser_is_instruction_string
    (asm_parser_instruction_t *instruction)
{
    bool status = true;

    RETURN_VALUE_IF(!instruction, false);
    status &= *str_begin(instruction->word) == '\"';
    status &= *str_end(instruction->word) == '\"';
    status &= !instruction->next;
    return status;
}

bool asm_parser_is_instruction_header(asm_parser_instruction_t *instruction)
{
    static bool has_name = false;
    static bool has_comment = false;
    bool status = false;

    RETURN_VALUE_IF(!instruction || !instruction->word, false);
    status |= my_strcmp(instruction->word, ".name") == 0;
    status |= my_strcmp(instruction->word, ".comment") == 0;
    status &= asm_parser_is_instruction_string(instruction->next);
    return status;
}
