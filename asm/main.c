/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** -> Assembly main
*/

#include <stdio.h>
#include "../include/my_macros.h"
#include "../include/asm.h"

int main(void)
{
    asm_parser_line_t *file = asm_parse_file("file.asm");
    asm_parser_line_t *const file_copy = file;
    asm_parser_instruction_t *instruction = file->instruction;

    RETURN_VALUE_IF(!file || !instruction, 84);
    do {
        instruction = file->instruction;
        do {
            printf("%s\t", instruction->word);
            instruction = instruction->next;
        } while (instruction);
        putchar('\n');
        file = file->next;
    } while (file && file->instruction);
    file = file_copy;
    asm_parser_free_line(&file);
    return 0;
}
