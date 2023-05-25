/*
** EPITECH PROJECT, 2023
** op.h
** File description:
** -> Operators and mnemonics for assembly
*/

#ifndef _OP_H_
    #define _OP_H_

    #include <stdint.h>
    #include <stdbool.h>

    // Should replace all these defines with constexpr variables
    // But GCC 13 doesn't fully support constexpr for now
    // constexpr char* doesn't compile with string literals

    #define N_OP                    16

    #define MEMORY_SIZE             (6 * 1'024)
    // Modulo of the index
    #define INDEX_MODULO            512
    // this may not be changed 2^*INDIRECT_SIZE
    #define MAX_ARGS_NUMBER         4

    #define COMMENT_CHAR            '#'
    #define LABEL_CHAR              ':'
    #define DIRECT_CHAR             '%'
    #define SEPARATOR_CHAR          ','

    #define LABEL_CHARS             "abcdefghijklmnopqrstuvwxyz_0123456789"

    #define NAME_CMD_STRING         ".name"
    #define COMMENT_CMD_STRING      ".comment"

    // Number of registers (r1 --> rx)
    #define REGISTERS_NUMBER              16

    typedef uint8_t args_type_t;

    typedef enum {
        PARAMETER_REGISTER = 1 << 0,
        PARAMETER_DIRECT = 1 << 1,
        PARAMETER_INDIRECT = 1 << 2,
        PARAMETER_LABEL = 1 << 3,
        PARAMETER_MAX = 1 + (1 << 3)
    } mnemonic_parameter_t;

    #ifdef ARGS_NO_INDEX
        #undef ARGS_NO_INDEX
    #endif
    #define ARGS_NO_INDEX { \
    }

    typedef struct op_s {
        char *mnemonic;
        unsigned char nbr_args;
        args_type_t type[MAX_ARGS_NUMBER];
        uint8_t opcode;
        uint16_t nbr_cycles;
        char *comment;
        bool are_args_indexes[MAX_ARGS_NUMBER];
    } op_t;


    // Size of parameters
    #define INDIRECT_SIZE           2
    #define INDEX_SIZE              INDIRECT_SIZE
    #define DIRECT_SIZE             4
    #define REGISTER_SIZE           DIRECT_SIZE

    extern op_t op_tab[N_OP];


    // Header
    #define PROG_NAME_LENGTH        128
    #define COMMENT_LENGTH          2'048
    // Magic number in the binary header
    #define COREWAR_EXEC_MAGIC      0x00'EA'83'F3
    #define HEADER_LENGTH (4 + PROG_NAME_LENGTH + 4 + COMMENT_LENGTH)

    typedef struct header_s {
        char prog_name[PROG_NAME_LENGTH + 1];
        uint32_t prog_size;
        char comment[COMMENT_LENGTH + 1];
    } header_t;

    enum {
        MNEMONIC_ERROR = 0x00,
        MNEMONIC_LIVE = 0x01,
        MNEMONIC_LD = 0x02,
        MNEMONIC_ST = 0x03,
        MNEMONIC_ADD = 0x04,
        MNEMONIC_SUB = 0x05,
        MNEMONIC_AND = 0x06,
        MNEMONIC_OR = 0x07,
        MNEMONIC_XOR = 0x08,
        MNEMONIC_ZJMP = 0x09,
        MNEMONIC_LDI = 0x0A,
        MNEMONIC_STI = 0x0B,
        MNEMONIC_FORK = 0x0C,
        MNEMONIC_LLD = 0x0D,
        MNEMONIC_LLDI = 0x0E,
        MNEMONIC_LFORK = 0x0F,
        MNEMONIC_AFF = 0x10,
        MNEMONIC_MAX = 0x11
    };

    #ifdef ARG_CODING_BITS
        #undef ARG_CODING_BITS
    #endif
    // Number of bits which encodes one parameter type
    #define PARAMETER_TYPE_BITS 2

    extern const mnemonic_parameter_t
        ARG_BITS_TO_NAME[1 << PARAMETER_TYPE_BITS];
    extern const unsigned ARG_NAME_TO_BITS[PARAMETER_MAX + 1];
    extern const unsigned ARG_SIZE[PARAMETER_MAX + 1];
    extern const bool MNEMONIC_HAS_NO_CODING_BYTE[MNEMONIC_MAX];

    // Live
    // number of cycle before being declared dead
    #define CYCLE_TO_DIE            1'536
    #define CYCLE_DELTA             5
    #define NBR_LIVE                40
#endif
