/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** -> Assembly main
*/

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/limits.h>
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
        my_dputs(STDERR_FILENO, "Syntax error !");
        free_main(file, labels);
        exit(84);
    }
    parser_add_size(*file);
}

STATIC_FUNCTION bool write_to_binary
    (char *source_filename, parser_line_t *file_content,
    parser_label_t *labels)
{
    static const int perms = S_IRGRP | S_IROTH | S_IRUSR | S_IWUSR;
    char output_filename[NAME_MAX] = {};
    int fd = -1;
    bool status = true;
    char *const last_slash = my_strrchr(source_filename, '/');
    char *const start = last_slash ? last_slash + 1 : source_filename;

    RETURN_VALUE_IF(!source_filename, false);
    my_strncpy(&output_filename[0], start, NAME_MAX);
    RETURN_VALUE_IF(output_filename[NAME_MAX - 5] != '\0', false);
    my_strcat(&output_filename[0], ".cor");
    fd = open(&output_filename[0], O_CREAT | O_TRUNC | O_RDWR, perms);
    RETURN_VALUE_IF(fd < 0, false);
    status = binary_write_file(fd, file_content, labels);
    close(fd);
    return status;
}

int main(int argc, char *argv[])
{
    parser_line_t *file = NULL;
    parser_label_t *labels = NULL;
    int return_code = 0;

    if (!argv[1] || argv[2]) {
        return 84;
    }
    display_help(argv);
    parse_file_and_labels(&file, &labels, argv);
    return_code = write_to_binary(argv[1], file, labels) ? 0 : 84;
    free_main(&file, &labels);
    return return_code;
}
