/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** -> Assembly main
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/my_macros.h"
#include "../include/my.h"
#include "../include/asm/asm.h"

/*
@brief
    Properly frees the main resources.
@param
    file is the address of the file linked list
@param
    labels if the address of the labels linked list
*/
STATIC_FUNCTION void free_main
    (parser_line_t **file, parser_label_t **labels)
{
    parser_free_line(file);
    parser_free_labels(labels);
}

/*
@brief
    Displays help if the firsr command-line argument is either -h or --help,
        and there's only one argument (except binary filename).
@param
    argv are the command line arguments
@note
    If the help message must be displayed, this functions exits the program
        with code 0.
@attention
    Regarding the note, this function obviously must be called before any
        parsing function, otherwise there will be memory leaks due to the exit.
*/
STATIC_FUNCTION void display_help(char *argv[])
{
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

STATIC_FUNCTION void parse_file_and_labels
    (parser_line_t **file, parser_label_t **labels, char *argv[])
{
    EXIT_IF(!file || !labels, 84);
    *file = parse_file(argv[1]);
    if (!(*file)) {
        my_dputs(STDERR_FILENO, "Parsing error !");
        exit(84);
    }
    if (!parse_labels(*file, labels)) {
        my_dputs(STDERR_FILENO, "Label error !");
        free_main(file, labels);
        exit(84);
    }
    if (!parser_check_syntax(*file)) {
        my_dputs(STDERR_FILENO, "Syntax error(s) !");
        free_main(file, labels);
        exit(84);
    }
}

STATIC_FUNCTION void print_debug(parser_line_t *file, parser_label_t *labels)
{
    parser_instruction_t *instruction = NULL;

    while (file) {
        instruction = file->instruction;
        while (instruction) {
            my_printf("%p : %s\n", instruction, instruction->word);
            instruction = instruction->next;
            my_putchar(instruction ? '\t' : '\n');
        }
        BREAK_IF(!file->next);
        file = file->next;
    }
    while (labels) {
        my_printf("%p : LABEL %s\n", (void*)labels->line, labels->name);
        BREAK_IF(!labels->next);
        labels = labels->next;
    }
    DOUBLY_LINKED_LIST_GO_TO_START(labels);
    DOUBLY_LINKED_LIST_GO_TO_START(file);
}

int main(int argc, char *argv[])
{
    parser_line_t *file = NULL;
    parser_label_t *labels = NULL;

    if (!argv[1] || argv[2]) {
        return 84;
    }
    display_help(argv);
    parse_file_and_labels(&file, &labels, argv);
    print_debug(file, labels);
    free_main(&file, &labels);
    return 0;
}
