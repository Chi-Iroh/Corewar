/*
** EPITECH PROJECT, 2023
** parser_remove_commas.c
** File description:
** -> Remove trailing comma after each operand
*/

#include "../include/asm.h"
#include "../include/my.h"

STATIC_FUNCTION void asm_parser_remove_single_instruction_separator
    (asm_parser_instruction_t *instruction)
{
    bool must_remove_comma = true;
    char *end = NULL;

    while (instruction && instruction->word) {
        end = str_end(instruction->word);
        must_remove_comma = !asm_parser_is_mnemonic(instruction->word);
        must_remove_comma &= end && *end == SEPARATOR_CHAR;
        if (must_remove_comma) {
            *end = '\0';
        }
        instruction = instruction->next;
    }
}

void asm_parser_remove_operand_separator(asm_parser_line_t *file)
{
    while (file && file->instruction) {
        asm_parser_remove_single_instruction_separator(file->instruction);
        file = file->next;
    }
}
