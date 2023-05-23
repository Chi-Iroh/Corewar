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
        .mnemonic = "live",
        .nbr_args = 1,
        .type = {
            PARAMETER_DIRECT
        },
        .are_args_indexes = ARGS_NO_INDEX,
        .opcode = 0x01,
        .nbr_cycles = 10,
        .comment = "alive"
    },
    {
        .mnemonic = "ld",
        .nbr_args = 2,
        .type = {
            PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_REGISTER
        },
        .are_args_indexes = ARGS_NO_INDEX,
        .opcode = 0x02,
        .nbr_cycles = 5,
        .comment = "load"
    },
    {
        .mnemonic = "st",
        .nbr_args = 2,
        .type = {
            PARAMETER_REGISTER,
            PARAMETER_INDIRECT | PARAMETER_REGISTER
        },
        .are_args_indexes = ARGS_NO_INDEX,
        .opcode = 0x03,
        .nbr_cycles = 5,
        .comment = "store"
    },
    {
        .mnemonic = "add",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER,
            PARAMETER_REGISTER,
            PARAMETER_REGISTER
        },
        .are_args_indexes = ARGS_NO_INDEX,
        .opcode = 0x04,
        .nbr_cycles = 10,
        .comment = "addition"
    },
    {
        .mnemonic = "sub",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER,
            PARAMETER_REGISTER,
            PARAMETER_REGISTER
        },
        .are_args_indexes = ARGS_NO_INDEX,
        .opcode = 0x05,
        .nbr_cycles = 10,
        .comment = "soustraction"
    },
    {
        .mnemonic = "and",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_REGISTER | PARAMETER_INDIRECT | PARAMETER_DIRECT,
            PARAMETER_REGISTER
        },
        .are_args_indexes = ARGS_NO_INDEX,
        .opcode = 0x06,
        .nbr_cycles = 6,
        .comment = "et (and  r1, r2, r3   r1&r2 -> r3"
    },
    {
        .mnemonic = "or",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER | PARAMETER_INDIRECT | PARAMETER_DIRECT,
            PARAMETER_REGISTER | PARAMETER_INDIRECT | PARAMETER_DIRECT,
            PARAMETER_REGISTER
        },
        .are_args_indexes = ARGS_NO_INDEX,
        .opcode = 0x07,
        .nbr_cycles = 6,
        .comment = "ou  (or   r1, r2, r3   r1 | r2 -> r3"
    },
    {
        .mnemonic = "xor",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER | PARAMETER_INDIRECT | PARAMETER_DIRECT,
            PARAMETER_REGISTER | PARAMETER_INDIRECT | PARAMETER_DIRECT,
            PARAMETER_REGISTER
        },
        .are_args_indexes = ARGS_NO_INDEX,
        .opcode = 0x08,
        .nbr_cycles = 6,
        .comment = "ou (xor  r1, r2, r3   r1^r2 -> r3"
    },
    {
        .mnemonic = "zjmp",
        .nbr_args = 1,
        .type = {
            PARAMETER_DIRECT
        },
        .are_args_indexes = {
            [0] = true
        },
        .opcode = 0x09,
        .nbr_cycles = 20,
        .comment = "jump if zero"
    },
    {
        .mnemonic = "ldi",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_DIRECT | PARAMETER_REGISTER,
            PARAMETER_REGISTER
        },
        .are_args_indexes = {
            [0] = true,
            [1] = true
        },
        .opcode = 0x0A,
        .nbr_cycles = 25,
        .comment = "load index"
    },
    {
        .mnemonic = "sti",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER,
            PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_DIRECT | PARAMETER_REGISTER
        },
        .are_args_indexes = {
            [1] = true,
            [2] = true
        },
        .opcode = 0x0B,
        .nbr_cycles = 25,
        .comment = "store index"
    },
    {
        .mnemonic = "fork",
        .nbr_args = 1,
        .type = {
            PARAMETER_DIRECT
        },
        .are_args_indexes = {
            [0] = true
        },
        .opcode = 0x0C,
        .nbr_cycles = 800,
        .comment = "fork"
    },
    {
        .mnemonic = "lld",
        .nbr_args = 2,
        .type = {
            PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_REGISTER
        },
        .are_args_indexes = ARGS_NO_INDEX,
        .opcode = 0x0D,
        .nbr_cycles = 10,
        .comment = "long load"
    },
    {
        .mnemonic = "lldi",
        .nbr_args = 3,
        .type = {
            PARAMETER_REGISTER | PARAMETER_DIRECT | PARAMETER_INDIRECT,
            PARAMETER_DIRECT | PARAMETER_REGISTER,
            PARAMETER_REGISTER
        },
        .are_args_indexes = {
            [0] = true,
            [1] = true
        },
        .opcode = 0x0E,
        .nbr_cycles = 50,
        .comment = "long load index"
    },
    {
        .mnemonic = "lfork",
        .nbr_args = 1,
        .type = {
            PARAMETER_DIRECT
        },
        .are_args_indexes = {
            [0] = true
        },
        .opcode = 0x0F,
        .nbr_cycles = 1000,
        .comment = "long fork"
    },
    {
        .mnemonic = "aff",
        .nbr_args = 1,
        .type = {
            PARAMETER_REGISTER
        },
        .are_args_indexes = ARGS_NO_INDEX,
        .opcode = 0x10,
        .nbr_cycles = 2,
        .comment = "aff"
    },
    {
        .mnemonic = NULL,
        .nbr_args = 0,
        .type = {0},
        .opcode = 0,
        .nbr_cycles = 0,
        .comment = NULL
    }
};

// Byte coding of each parameter type (00 = PARAMETER_MAX = no parameter)
const mnemonic_parameter_t ARGS_BITS_TO_NAME[1 << PARAMETER_TYPE_BITS] = {
    [0b00] = PARAMETER_MAX,
    [0b01] = PARAMETER_REGISTER,
    [0b10] = PARAMETER_DIRECT,
    [0b11] = PARAMETER_INDIRECT
};

const unsigned ARGS_NAME_TO_BITS[PARAMETER_MAX + 1] = {
    [PARAMETER_MAX] = 0b00,
    [PARAMETER_REGISTER] = 0b01,
    [PARAMETER_DIRECT] = 0b10,
    [PARAMETER_INDIRECT] = 0b11
};

// Size of each parameter type
const unsigned ARGS_SIZE[PARAMETER_MAX + 1] = {
    [PARAMETER_DIRECT] = DIRECT_SIZE,
    [PARAMETER_INDIRECT] = INDIRECT_SIZE,
    [PARAMETER_REGISTER] = REGISTER_SIZE,
};

const bool MNEMONIC_HAS_NO_CODING_BYTE[MNEMONIC_MAX] = {
    [MNEMONIC_LIVE] = true,
    [MNEMONIC_ZJMP] = true,
    [MNEMONIC_FORK] = true,
    [MNEMONIC_LFORK] = true
};
