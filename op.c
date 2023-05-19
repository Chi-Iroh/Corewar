/*
** EPITECH PROJECT, 2023
** op.c
** File description:
** -> Operators and mnemonics for assembly
*/

#include <stdlib.h>
#include "include/op.h"

op_t op_tab[N_OP] = {
    {
        .mnemonique = "live",
        .nbr_args = 1,
        .type = {
            PARAMETER_DIRECT
        },
        .code = 1,
        .nbr_cycles = 10,
        .comment = "alive"
    },
    {
        .mnemonique = "ld",
        .nbr_args = 2,
        .type = {
            PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_REGISTER
        },
        .code = 2,
        .nbr_cycles = 5,
        .comment = "load"
    },
    {
        .mnemonique = "st",
        .nbr_args = 2,
        .type = {
            PARAMETER_REGISTER,
            PARAMETER_INDIRECT | PARAMETER_REGISTER
        },
        .code = 3,
        .nbr_cycles = 5,
        .comment = "store"
    },
    {
        .mnemonique = "add",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER,
            PARAMETER_REGISTER,
            PARAMETER_REGISTER
        },
        .code = 4,
        .nbr_cycles = 10,
        .comment = "addition"
    },
    {
        .mnemonique = "sub",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER,
            PARAMETER_REGISTER,
            PARAMETER_REGISTER
        },
        .code = 5,
        .nbr_cycles = 10,
        .comment = "soustraction"
    },
    {
        .mnemonique = "and",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_REGISTER | PARAMETER_INDIRECT | PARAMETER_DIRECT,
            PARAMETER_REGISTER
        },
        .code = 6,
        .nbr_cycles = 6,
        .comment = "et (and  r1, r2, r3   r1&r2 -> r3"
    },
    {
        .mnemonique = "or",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER | PARAMETER_INDIRECT | PARAMETER_DIRECT,
            PARAMETER_REGISTER | PARAMETER_INDIRECT | PARAMETER_DIRECT,
            PARAMETER_REGISTER
        },
        .code = 7,
        .nbr_cycles = 6,
        .comment = "ou  (or   r1, r2, r3   r1 | r2 -> r3"
    },
    {
        .mnemonique = "xor",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER | PARAMETER_INDIRECT | PARAMETER_DIRECT,
            PARAMETER_REGISTER | PARAMETER_INDIRECT | PARAMETER_DIRECT,
            PARAMETER_REGISTER
        },
        .code = 8,
        .nbr_cycles = 6,
        .comment = "ou (xor  r1, r2, r3   r1^r2 -> r3"
    },
    {
        .mnemonique = "zjmp",
        .nbr_args = 1,
        .type = {PARAMETER_DIRECT},
        .code = 9,
        .nbr_cycles = 20,
        .comment = "jump if zero"
    },
    {
        .mnemonique = "ldi",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_DIRECT | PARAMETER_REGISTER,
            PARAMETER_REGISTER
        },
        .code = 10,
        .nbr_cycles = 25,
        .comment = "load index"
    },
    {
        .mnemonique = "sti",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER,
            PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_DIRECT | PARAMETER_REGISTER
        },
        .code = 11,
        .nbr_cycles = 25,
        .comment = "store index"
    },
    {
        .mnemonique = "fork",
        .nbr_args = 1,
        .type = {
            PARAMETER_DIRECT
        },
        .code = 12,
        .nbr_cycles = 800,
        .comment = "fork"
    },
    {
        .mnemonique = "lld",
        .nbr_args = 2,
        .type = {
            PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_REGISTER
        },
        .code = 13,
        .nbr_cycles = 10,
        .comment = "long load"
    },
    {
        .mnemonique = "lldi",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_DIRECT | PARAMETER_REGISTER,
            PARAMETER_REGISTER
        },
        .code = 14,
        .nbr_cycles = 50,
        .comment = "long load index"
    },
    {
        .mnemonique = "lfork",
        .nbr_args = 1,
        .type = {
            PARAMETER_DIRECT
        },
        .code = 15,
        .nbr_cycles = 1000,
        .comment = "long fork"
    },
    {
        .mnemonique = "aff",
        .nbr_args = 1,
        .type = {
            PARAMETER_REGISTER
        },
        .code = 16,
        .nbr_cycles = 2,
        .comment = "aff"
    },
    {
        .mnemonique = NULL,
        .nbr_args = 0,
        .type = {0},
        .code = 0,
        .nbr_cycles = 0,
        .comment = NULL
    }
};
