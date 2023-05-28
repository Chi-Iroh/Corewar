/*
** EPITECH PROJECT, 2023
** skip_labels.c
** File description:
** -> Skips labels while encoding instructions
*/

#include "../include/my_macros.h"
#include "../include/asm/asm.h"

void skip_labels(parser_instruction_t **instruction_address)
{
    char *word = NULL;

    RETURN_IF(!instruction_address || !(*instruction_address));
    word = (*instruction_address)->word;
    while (*instruction_address && parser_is_label(word, LABEL_COLON_END)) {
        *instruction_address = (*instruction_address)->next;
        if (*instruction_address) {
            word = (*instruction_address)->word;
        }
    }
}
