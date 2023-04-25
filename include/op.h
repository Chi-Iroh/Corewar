/*
** EPITECH PROJECT, 2023
** op.h
** File description:
** -> Operators and mnemonics for assembly
*/

#ifndef _OP_H_
    #define _OP_H_

    #define N_OP 17
    #define LAST_OP (N_OP - 1)

    #define MEM_SIZE                (6 * 1024)
    // Modulo of the index
    #define IDX_MOD                 512
    // this may not be changed 2^*IND_SIZE
    #define MAX_ARGS_NUMBER         4

    #define COMMENT_CHAR            '#'
    #define LABEL_CHAR              ':'
    #define DIRECT_CHAR             '%'
    #define SEPARATOR_CHAR          ','

    #define LABEL_CHARS             "abcdefghijklmnopqrstuvwxyz_0123456789"

    #define NAME_CMD_STRING         ".name"
    #define COMMENT_CMD_STRING      ".comment"

    // Number of registers (r1 --> rx)
    #define REG_NUMBER      16

    typedef char args_type_t;

    // register
    #define T_REG           1
    // direct (ld #1, r1 = put 1 into r1)
    #define T_DIR           2
    // indirect (ld 1, r1 = put what's in the address (1+pc) into r1 (4bytes))
    #define T_IND           4

    // Label
    #define T_LAB           8

    typedef struct op_s {
        char *mnemonique;
        char nbr_args;
        args_type_t type[MAX_ARGS_NUMBER];
        char code;
        int nbr_cycles;
        char *comment;
    } op_t;


    // Size
    #define IND_SIZE        2
    #define DIR_SIZE        4
    #define REG_SIZE        DIR_SIZE

    extern op_t op_tab[];


    // Header
    #define PROG_NAME_LENGTH        128
    #define COMMENT_LENGTH          2048
    #define COREWAR_EXEC_MAGIC      0xea83f3        /* why not */

    typedef struct header_s {
        int magic;
        char prog_name[PROG_NAME_LENGTH + 1];
        int prog_size;
        char comment[COMMENT_LENGTH + 1];
    } header_t;

    // Live

    // number of cycle before beig declared dead
    #define CYCLE_TO_DIE    1536
    #define CYCLE_DELTA     5
    #define NBR_LIVE        40
#endif
