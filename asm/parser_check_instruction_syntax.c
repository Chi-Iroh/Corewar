/*
** EPITECH PROJECT, 2023
** parser_check_instruction_syntax.c
** File description:
** -> Checks instruction's syntax
*/

#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/asm/asm.h"

STATIC_FUNCTION bool parser_is_arg_label(char *word);

bool (*parser_syntax_functions[PARAMETER_MAX])(char*) = {
    [PARAMETER_REGISTER] = parser_is_register,
    [PARAMETER_DIRECT] = parser_is_direct_value,
    [PARAMETER_INDIRECT] = parser_is_indirect_value,
    [PARAMETER_LABEL] = parser_is_arg_label
};

const unsigned parser_word_types[PARSER_WORD_TYPES] = {
    PARAMETER_REGISTER,
    PARAMETER_DIRECT,
    PARAMETER_INDIRECT,
    PARAMETER_LABEL
};

/*
@brief
    Wraps the function parser_is_label with a "default value", to be used
        in the below array of function pointers.
@note
    Exactly the same as parser_is_label(word, LABEL_COLON_END)
*/
STATIC_FUNCTION bool parser_is_arg_label(char *word)
{
    return parser_is_label(word, LABEL_COLON_END);
}

/*
@brief
    Iterates over the global variable op_tab to find mnemonic.
@param
    mnemonic is the mnemonic (as ld or add) to search
@returns
    N_OP if not found (op_tab's size), otherwise its index
*/
STATIC_FUNCTION unsigned parser_op_tab_mnemonic_index(char *mnemonic)
{
    RETURN_VALUE_IF(!mnemonic, N_OP);
    for (unsigned i = 0; i < LAST_OP; i++) {
        if (my_strcmp(mnemonic, op_tab[i].mnemonic) == 0) {
            return i;
        }
    }
    return N_OP;
}

/*
@brief
    Checks if a mnemonic's i-th arg is in a legal type or not.
@param
    arg is the argument string
    arg_i is the index of the arg (2nd arg <-> arg_i = 1)
    op_tab_index is the index of the current mnemonic in op_tab
@returns
    true if arg is in a legal type, otherwise false
*/
STATIC_FUNCTION bool parser_is_arg_type_ok
(char *arg, unsigned arg_i, unsigned op_tab_index)
{
    op_t *const instruction = &op_tab[op_tab_index];
    unsigned parser_word_type = 0;

    RETURN_VALUE_IF(!arg, false);
    if (arg_i == 0) {
        return my_strcmp(instruction->mnemonic, arg) == 0;
    }
    for (unsigned j = 0; j < PARSER_WORD_TYPES; j++) {
        parser_word_type = parser_word_types[j];
        if (!(instruction->type[arg_i - 1] & parser_word_type)) {
            continue;
        }
        if (parser_syntax_functions[parser_word_type](arg)) {
            return true;
        }
    }
    return false;
}

/*
@brief
    Checks if an instruction is legal.
@param
    instruction is the instruction node to check
@returns
    true if instruction has a legal group of mnemonic and eventual args
@note
    the final comparison between instruction and NULL aims to ensure that the
    mnemonic exactly has the good number of arguments.
    If instruction isn't NULL, it means that it is connected with another node
    we don't want.
*/
STATIC_FUNCTION bool parser_check_instruction_syntax
    (parser_instruction_t *instruction)
{
    unsigned index = 0;
    unsigned nb_args = 0;

    RETURN_VALUE_IF(!instruction || !instruction->word, false);
    RETURN_VALUE_IF(!parser_is_mnemonic(instruction->word), false);
    index = parser_op_tab_mnemonic_index(instruction->word);
    RETURN_VALUE_IF(index == N_OP, false);
    instruction = instruction->next;
    nb_args = op_tab[index].nbr_args;
    for (unsigned i = 1; i <= nb_args; i++) {
        if (!instruction) {
            return false;
        }
        if (!parser_is_arg_type_ok(instruction->word, i, index)) {
            return false;
        }
        instruction = instruction->next;
    }
    return instruction == NULL;
}

/*
@brief
    Checks if a file's syntax is OK.
@param
    file is the file linked list.
@returns
    true if syntax is ok, false otherwise (or if file is NULL).
*/
bool parser_check_syntax(parser_line_t *file)
{
    parser_instruction_t *after_labels = file ? file->instruction : NULL;
    bool status = false;

    RETURN_VALUE_IF(!file, false);
    parser_remove_operand_separator(file);
    while (file) {
        after_labels = file->instruction;
        while (after_labels &&
            parser_is_label(after_labels->word, LABEL_COLON_END)) {
            after_labels = after_labels->next;
        }
        if (after_labels) {
            status = parser_is_instruction_header(after_labels);
            status |= parser_check_instruction_syntax(after_labels);
            RETURN_VALUE_IF(!status, false);
        }
        file = file->next;
    }
    return true;
}
