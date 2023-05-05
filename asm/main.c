/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** -> Assembly main
*/

#include <stdio.h>
#include "../include/my_macros.h"
#include "../include/my.h"
#include "../include/asm.h"

int main(int argc, char *argv[])
{
    RETURN_VALUE_IF(!argv[1], 84);
    asm_parser_line_t *file = asm_parse_file(argv[1]);
    asm_parser_line_t *const file_copy = file;
    asm_parser_instruction_t *instruction = file->instruction;

    RETURN_VALUE_IF(!file || !instruction, 84);
    my_printf("Syntax %s\n", asm_parser_check_syntax(file) ? "OK" : "KO");
    do {
        instruction = file->instruction;
        do {
            my_printf("'%s'\t", instruction->word);
            instruction = instruction->next;
        } while (instruction);
        my_putchar('\n');
        file = file->next;
    } while (file && file->instruction);
    file = file_copy;
    asm_parser_free_line(&file);
    return 0;
}
