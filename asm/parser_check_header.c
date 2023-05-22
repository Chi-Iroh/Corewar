/*
** EPITECH PROJECT, 2023
** parser_check_header.c
** File description:
** -> Checks for header instructions.
*/

#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/asm/asm.h"

/*
@brief
    Checks if an instruction is a string (text surrounded by double quotes).
@param
    instruction is the instruction to check
@returns
    false if NULL pointer or instruction isn't a string, otherwise true
*/
STATIC_FUNCTION bool parser_is_instruction_string
    (parser_instruction_t *instruction)
{
    bool status = true;

    RETURN_VALUE_IF(!instruction, false);
    status &= *str_begin(instruction->word) == '\"';
    status &= *str_end(instruction->word) == '\"';
    status &= !instruction->next;
    return status;
}

/*
@brief
    Checks if an instruction is a header instruction (.name or .comment)
        and has a following string.
@param
    instruction is the instruction to check
@returns
    false if NULL pointer or instruction isn't a header instruction,
        otherwise true
*/
bool parser_is_instruction_header(parser_instruction_t *instruction)
{
    static bool has_name = false;
    static bool has_comment = false;
    bool status = false;

    RETURN_VALUE_IF(!instruction || !instruction->word, false);
    if (my_strcmp(instruction->word, NAME_CMD_STRING) == 0 && !has_name) {
        status = true;
        has_name = true;
    }
    if (my_strcmp(instruction->word,COMMENT_CMD_STRING) == 0 && !has_comment) {
        status = true;
        has_comment = true;
    }
    status = status && parser_is_instruction_string(instruction->next);
    return status;
}
