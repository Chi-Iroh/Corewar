/*
** EPITECH PROJECT, 2023
** parser_size.c
** File description:
** -> Computes the siz of each element
*/

#include "../include/my_macros.h"
#include "../include/asm/asm.h"

STATIC_FUNCTION void parser_add_line_size(parser_line_t *single_line)
{
    parser_instruction_t *instruction = NULL;
    unsigned index = 0;
    unsigned arg_index = 0;
    bool is_index = false;

    instruction = single_line ? single_line->instruction : NULL;
    while (instruction && !parser_is_mnemonic(instruction->word)) {
        instruction = instruction->next;
    }
    RETURN_IF(!instruction || !instruction->word);
    index = mnemonic_index(instruction->word);
    instruction->size = 1 + !MNEMONIC_HAS_NO_CODING_BYTE[op_tab[index].opcode];
    instruction = instruction->next;
    while (instruction) {
        is_index = !parser_is_register(instruction->word);
        instruction->size = ARG_SIZE[instruction_get_arg_type(instruction)];
        is_index &= op_tab[index].are_args_indexes[arg_index++];
        instruction->size = is_index ? INDIRECT_SIZE : instruction->size;
        instruction = instruction->next;
    }
}

void parser_add_size(parser_line_t *file)
{
    RETURN_IF(!file);
    while (file) {
        parser_add_line_size(file);
        file = file->next;
    }
}

uint64_t parser_get_file_size(parser_line_t *file)
{
    parser_instruction_t *instruction = NULL;
    uint64_t size = 0;

    RETURN_VALUE_IF(!file, 0);
    while (file) {
        instruction = file->instruction;
        while (instruction) {
            size += instruction->size;
            instruction = instruction->next;
        }
        file = file->next;
    }
    return size;
}
