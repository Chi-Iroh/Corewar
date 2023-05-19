/*
** EPITECH PROJECT, 2023
** op.h
** File description:
** -> Operators and mnemonics for assembly
*/

#ifndef _OP_H_
    #define _OP_H_

    #include <stdint.h>

    // Should replace all these defines with constexpr variables
    // But GCC 13 doesn't fully support constexpr for now
    // constexpr char* doesn't compile with string literals

    #define N_OP                    17
    #define LAST_OP                 (N_OP - 1)

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
    } asm_parameter_t;

    typedef struct op_s {
        char *mnemonique;
        unsigned char nbr_args;
        args_type_t type[MAX_ARGS_NUMBER];
        uint8_t code;
        uint16_t nbr_cycles;
        char *comment;
    } op_t;


    // Size of parameters
    #define INDIRECT_SIZE           2
    #define DIRECT_SIZE             4
    #define REGISTER_SIZE           DIRECT_SIZE

    extern op_t op_tab[N_OP];


    // Header
    #define PROG_NAME_LENGTH        128
    #define COMMENT_LENGTH          2'048
    // Magic number in the binary header
    #define COREWAR_EXEC_MAGIC      0xEA'83'F3

    typedef struct header_s {
        uint32_t magic;
        char prog_name[PROG_NAME_LENGTH + 1];
        unsigned prog_size;
        char comment[COMMENT_LENGTH + 1];
    } header_t;

    // Live
    // number of cycle before being declared dead
    #define CYCLE_TO_DIE            1'536
    #define CYCLE_DELTA             5
    #define NBR_LIVE                40
#endif
