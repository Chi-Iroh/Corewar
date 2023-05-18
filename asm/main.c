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

STATIC_FUNCTION void free_main
    (asm_parser_line_t **file, asm_parser_label_t **labels)
{
    asm_parser_free_line(file);
    asm_parser_free_labels(labels);
}

int main(int argc, char *argv[])
{
    RETURN_VALUE_IF(!argv[1], 84);
    asm_parser_line_t *file = asm_parse_file(argv[1]);
    asm_parser_line_t *const file_copy = file;
    asm_parser_instruction_t *instruction = file->instruction;
    asm_parser_label_t *labels = NULL;

    RETURN_VALUE_IF(!file || !instruction, 84);
    if (!asm_parse_labels(file, &labels)) {
        free_main(&file, &labels);
        return 84;
    }
    my_printf("Syntax %s\n", asm_parser_check_syntax(file) ? "OK" : "KO");
    while (file) {
        instruction = file->instruction;
        while (instruction) {
            my_printf("%p : %s\n", instruction, instruction->word);
            instruction = instruction->next;
            if (instruction) {
                my_putchar('\t');
            }
        }
        my_putchar('\n');
        file = file->next;
    }
    while (labels) {
        printf("%p : LABEL %s\n", labels->line, labels->name);
        if (!labels->next) {
            break;
        }
        labels = labels->next;
    }
    while (labels->previous) {
        labels = labels->previous;
    }
    file = file_copy;
    free_main(&file, &labels);
    return 0;
}
