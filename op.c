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
        .opcode = MNEMONIC_LIVE,
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
        .opcode = MNEMONIC_LD,
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
        .opcode = MNEMONIC_ST,
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
        .opcode = MNEMONIC_ADD,
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
        .opcode = MNEMONIC_SUB,
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
        .opcode = MNEMONIC_AND,
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
        .opcode = MNEMONIC_OR,
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
        .opcode = MNEMONIC_XOR,
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
        .opcode = MNEMONIC_ZJMP,
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
        .opcode = MNEMONIC_LDI,
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
        .opcode = MNEMONIC_STI,
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
        .opcode = MNEMONIC_FORK,
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
        .opcode = MNEMONIC_LLD,
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
        .opcode = MNEMONIC_LLDI,
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
        .opcode = MNEMONIC_LFORK,
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
        .opcode = MNEMONIC_AFF,
        .nbr_cycles = 2,
        .comment = "aff"
    }
};

// Byte coding of each parameter type (00 = PARAMETER_MAX = no parameter)
const mnemonic_parameter_t ARG_BITS_TO_NAME[1 << PARAMETER_TYPE_BITS] = {
    [0b00] = PARAMETER_MAX,
    [0b01] = PARAMETER_REGISTER,
    [0b10] = PARAMETER_DIRECT,
    [0b11] = PARAMETER_INDIRECT
};

const unsigned ARG_NAME_TO_BITS[PARAMETER_MAX + 1] = {
    [PARAMETER_MAX] = 0b00,
    [PARAMETER_REGISTER] = 0b01,
    [PARAMETER_DIRECT] = 0b10,
    [PARAMETER_INDIRECT] = 0b11
};

// Size of each parameter type
const unsigned ARG_SIZE[PARAMETER_MAX + 1] = {
    [PARAMETER_DIRECT] = DIRECT_SIZE,
    [PARAMETER_INDIRECT] = INDIRECT_SIZE,
    [PARAMETER_REGISTER] = 1,
};

/*
If a parameter is a label as a direct value (%:label), then it's encoded
    as the number of bytes to jump.
If the label's address is lower than the pc, then the arg is something like
    0xFF'F5, which means pc must be decreased of its difference with
    0x01'00'00, here 11 bytes.
Else, the arg will be something like 0x00'05, which means pc must be
    increased of 5 bytes.
As the memory is much smaller than the max value fitting in 2 bytes
    (65535), then this notation isn't ambiguous, if arg1 > MEM_SIZE,
    pc must be decreased, otherwise pc must be increased.
*/
const bool MNEMONIC_HAS_NO_CODING_BYTE[MNEMONIC_MAX] = {
    [MNEMONIC_LIVE] = true,
    [MNEMONIC_ZJMP] = true,
    [MNEMONIC_FORK] = true,
    [MNEMONIC_LFORK] = true
};
