/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** -> Assembly main
*/

#include <stdio.h>
#include "../include/asm.h"

asm_parser_line_t *asm_parser_split_line(char *line);

int main(void)
{
    asm_parser_line_t *line = asm_parser_split_line("sti %4 %:label");
    asm_parser_instruction_t *instruction = line->instruction;

    if (!line) {
        return 1;
    }
    while (instruction->previous) {
        instruction = instruction->previous;
    }
    while (true) {
        printf("%s\n", instruction->word);
        if (instruction->next) {
            instruction = instruction->next;
        } else {
            break;
        }
    }
    asm_parser_free_line(&line);
    return 0;
}
