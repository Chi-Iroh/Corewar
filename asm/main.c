/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** -> Assembly main
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/my_macros.h"
#include "../include/my.h"
#include "../include/asm/asm.h"

STATIC_FUNCTION void free_main
    (parser_line_t **file, parser_label_t **labels)
{
    parser_free_line(file);
    parser_free_labels(labels);
}

STATIC_FUNCTION void display_help(char *argv[])
{
    if (!argv[1]) {
        return;
    }
    if (my_strcmp(argv[1], "-h") * my_strcmp(argv[1], "--help") == 0) {
        my_puts(
            "USAGE\n"
            "./asm file_name[.s]\n"
            "DESCRIPTION\n"
            "file_name file in assembly language to be converted info "
                "file_name.cor, an\n"
            "executable in the Virtual Machine."
        );
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    display_help(argv);
    RETURN_VALUE_IF(!argv[1], 84);
    parser_line_t *file = parse_file(argv[1]);
    parser_line_t *const file_copy = file;
    parser_instruction_t *instruction = file->instruction;
    parser_label_t *labels = NULL;

    RETURN_VALUE_IF(!file || !instruction, 84);
    if (!parse_labels(file, &labels)) {
        free_main(&file, &labels);
        return 84;
    }
    my_printf("Syntax %s\n", parser_check_syntax(file) ? "OK" : "KO");
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
