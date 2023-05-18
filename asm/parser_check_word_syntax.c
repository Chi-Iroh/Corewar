/*
** EPITECH PROJECT, 2023
** parser_check_syntax.c
** File description:
** -> Checks syntax of each word
*/

#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/asm/asm.h"

/*
@brief
    Checks if an instruction is a mnemonic (as ld or add) or not.
@param
    word is the string to parse.
@returns
    false if either word is NULL or isn't a mnemonic, otherwise true.
*/
bool parser_is_mnemonic(char *word)
{
    RETURN_VALUE_IF(!word, false);
    for (unsigned i = 0; i < LAST_OP; i++) {
        if (my_strcmp(op_tab[i].mnemonique, word) == 0) {
            return true;
        }
    }
    return false;
}

/*
@brief
    Checks if an instruction is a label (as hello: or world:).
@param
    word is the string to parse
@param
    colon_pos is the position of the colon (:) in the label,
        at the end, at the beginning or nowwhere (check asm.h).
@returns
    false if either word is NULL or isn't a label, otherwise true.
*/
bool parser_is_label(char *word, parser_label_colon_pos_t colon_pos)
{
    size_t i = 0;
    char c = word ? word[0] : '\0';

    RETURN_VALUE_IF(!word || !word[0], false);
    if (colon_pos == LABEL_COLON_BEGIN && (c != LABEL_CHAR || !word[1])) {
        return false;
    }
    for (i = (colon_pos == LABEL_COLON_BEGIN); word[i]; i++) {
        c = word[i];
        if (colon_pos == LABEL_COLON_END && c == LABEL_CHAR && !word[i + 1]) {
            return i > 0;
        }
        if (!my_strchr(LABEL_CHARS, word[i])) {
            return false;
        }
    }
    return colon_pos != LABEL_COLON_END;
}

/*
@brief
    Checks if an instruction is a direct value (as %4 or %:label) or not.
@param
    word is the string to parse.
@returns
    false if either word is NULL or isn't a direct value, otherwise true.
*/
bool parser_is_direct_value(char *word)
{
    const bool begins_with_percent = word ? word[0] == DIRECT_CHAR : false;

    RETURN_VALUE_IF(!begins_with_percent, false);
    if (word[1] && !str_find_not_pred(&word[1], my_isdigit)) {
        return true;
    }
    return parser_is_label(&word[1], LABEL_COLON_BEGIN);
}

/*
@brief
    Checks if an instruction is an indirect value (as 4 or :label) or not.
@param
    word is the string to parse.
@returns
    false if either word is NULL or isn't an indirect value, otherwise true.
*/
bool parser_is_indirect_value(char *word)
{
    RETURN_VALUE_IF(!word || !word[0], false);
    if (!str_find_not_pred(word, my_isdigit)) {
        return true;
    }
    return parser_is_label(word, LABEL_COLON_BEGIN);
}

/*
@brief
    Checks if an instruction is an register (r1 --> rREG_NUMBER) or not.
@param
    word is the string to parse.
@returns
    false if either word is NULL or isn't a register, otherwise true.
*/
bool parser_is_register(char *word)
{
    const bool status = word && word[0] == 'r' && word[1];
    const intmax_t n = status ? my_getnbr(&word[1]) : 0;

    RETURN_VALUE_IF(!status, false);
    if (str_find_not_pred(&word[1], my_isdigit)) {
        return false;
    }
    return n >= 1 && n <= REG_NUMBER;
}
