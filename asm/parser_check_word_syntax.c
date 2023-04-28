/*
** EPITECH PROJECT, 2023
** parser_check_syntax.c
** File description:
** -> Checks syntax of each word
*/

#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/asm.h"

/*
@brief
    Checks if an instruction is a mnemonic (as ld or add) or not.
@param
    word the string to parse.
@returns
    false if either word is NULL or isn't a mnemonic, true otherwise.
*/
bool asm_parser_is_mnemonic(char *word)
{
    RETURN_VALUE_IF(!word, false);
    for (unsigned i = 0; i < LAST_OP; i++) {
        if (my_strcmp(op_tab[i].mnemonique, word) == 0) {
            return true;
        }
    }
    return false;
}

bool asm_parser_is_label(char *word)
{
    RETURN_VALUE_IF(!word || word[0] != LABEL_CHAR || !word[1], false);
    for (size_t i = 1; word[i]; i++) {
        if (!my_strchr(LABEL_CHARS, word[i])) {
            return false;
        }
    }
    return true;
}

/*
@brief
    Checks if an instruction is a direct value (as %4 or %:label) or not.
@param
    word the string to parse.
@returns
    false if either word is NULL or isn't a direct value, true otherwise.
*/
bool asm_parser_is_direct_value(char *word)
{
    const bool status = word;
    const bool begins_with_percent = status ?
        word[0] == DIRECT_CHAR : false;

    RETURN_VALUE_IF(!status || !begins_with_percent, false);
    if (word[1] && !str_find_not_pred(&word[1], my_isdigit)) {
        return true;
    }
    return asm_parser_is_label(&word[1]);
}

/*
@brief
    Checks if an instruction is an indirect value (as 4 or :label) or not.
@param
    word the string to parse.
@returns
    false if either word is NULL or isn't an indirect value, true otherwise.
*/
bool asm_parser_is_indirect_value(char *word)
{
    RETURN_VALUE_IF(!word || !word[0], false);
    if (!str_find_not_pred(word, my_isdigit)) {
        return true;
    }
    return asm_parser_is_label(word);
}

/*
@brief
    Checks if an instruction is an register (r1 --> rREG_NUMBER) or not.
@param
    word the string to parse.
@returns
    false if either word is NULL or isn't a register, true otherwise.
*/
bool asm_parser_is_register(char *word)
{
    const bool status = word && word[0] == 'r' && word[1];
    const intmax_t n = status ? my_getnbr(&word[1]) : 0;

    RETURN_VALUE_IF(!status, false);
    if (str_find_not_pred(&word[1], my_isdigit)) {
        return false;
    }
    return n >= 1 && n <= REG_NUMBER;
}
