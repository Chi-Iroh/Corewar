/*
** EPITECH PROJECT, 2023
** str_begin.c
** File description:
** -> Looks for the first non-space character of a string.
*/

#include "../include/my.h"

/*
@brief
    Returns the first non-space character of a string.
@param
    str is the string to read.
@returns
    '\0' is str is NULL or space-only, otherwise the first non-space character.
*/
char str_begin(char *str)
{
    if (!str) {
        return '\0';
    }
    str_advance_pred(&str, my_isspace);
    return *str;
}
