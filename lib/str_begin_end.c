/*
** EPITECH PROJECT, 2023
** str_begin.c
** File description:
** -> Looks for the first non-space character of a string.
*/

#include "../include/my.h"

/*
@brief
    Returns a pointer to first non-space character of a string.
@param
    str is the string to read.
@returns
    NULL is str is NULL or space-only,
        otherwise a pointer to the first non-space character.
*/
char *str_begin(char *str)
{
    if (!str) {
        return NULL;
    }
    str_advance_pred(&str, my_isspace);
    return str;
}

/*
@brief
    Returns a pointer to the last non-space character of a string.
@param
    str is the string to read.
@returns
    NULL is str is NULL or space-only,
        otherwise a pointer to the last non-space character.
*/
char *str_end(char *str)
{
    char *const c = str ? str_rfind_not_pred(str, my_isspace) : NULL;

    if (!str) {
        return NULL;
    }
    return c;
}
