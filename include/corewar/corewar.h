/*
** EPITECH PROJECT, 2023
** corewar.h
** File description:
** -> Header for VM part
*/

#pragma once

#include "corewar_config.h"
#include "corewar_types.h"
#include "../op.h"

uintmax_t mnemonic_get_arg
    (vm_mnemonic_t args, unsigned index, vm_champion_t *champion);
uintmax_t mnemonic_get_indirect_address_value
    (vm_t *vm, mnemonic_parameter_t type, uintmax_t value);

void my_memcpy(void *destination, void *source, size_t size);
void my_memset(void *destination, uint8_t byte, size_t size);

void dump_memory(vm_t *vm, unsigned n_32bytes_chunks);

bool mnemonic_are_args_ok(vm_mnemonic_t args);
bool mnemonic_ld(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);
bool mnemonic_st(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);
bool mnemonic_add(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);
bool mnemonic_sub(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);
bool mnemonic_and(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);
bool mnemonic_or(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);
bool mnemonic_xor(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);
bool mnemonic_zjmp(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);
bool mnemonic_ldi(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);
bool mnemonic_sti(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);
bool mnemonic_lld(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);
bool mnemonic_lldi(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);
bool mnemonic_aff(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);
bool mnemonic_live(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);
bool mnemonic_fork(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);
bool mnemonic_lfork(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args);

#ifdef ARG_CODING_BITS
    #undef ARG_CODING_BITS
#endif
// Number of bits which encodes one parameter type
#define PARAMETER_TYPE_BITS 2

extern const mnemonic_parameter_t ARGS_BITS_TO_NAME[1 << PARAMETER_TYPE_BITS];
extern const unsigned ARGS_NAME_TO_BITS[PARAMETER_MAX + 1];
extern const unsigned ARGS_SIZE[PARAMETER_MAX + 1];

bool vm_init(vm_t *vm, char *argv[]);

vm_mnemonic_t parse_instruction(vm_t *vm, vm_address_t address);
bool parse_argv_is_flag(char *str);
void parse_argv(vm_t *vm, unsigned argc, char *argv[]);

bool champions_has_prog_number
    (vm_t *champions, vm_address_t prog_number);
bool champions_next_prog_number
    (vm_t *vm, vm_address_t *prog_number);
void champion_duplicate(vm_t *vm, vm_champion_t *parent);
void champion_remove(vm_t *vm, vm_address_t champion);

bool binary_load_at(vm_t *vm, char *binary, vm_address_t load_address);
bool binary_argv_load_single_binary
    (vm_t *vm, unsigned argc, char *argv[], unsigned *index);
bool binary_load_all(vm_t *vm, unsigned argc, char *argv[]);

bool memory_read_n_bytes
    (vm_t *vm, vm_address_t *address, vm_address_t n_bytes, uintmax_t *arg);
vm_address_t index_apply_to_pc
    (vm_address_t pc, vm_indirect_arg_t index,
    bool apply_index_modulo);

void scheduler_execute(vm_t *vm);

extern const vm_champion_t CHAMPION_DEFAULT;
extern const char *const HELP_MSG;

extern const bool (*MNEMONICS[MNEMONIC_MAX])
    (vm_t *, vm_champion_t *, vm_mnemonic_t);

extern const bool MNEMONIC_HAS_NO_CODING_BYTE[MNEMONIC_MAX];

extern const char *const PRINTF_COLOR_RED;
extern const char *const PRINTF_COLOR_GREEN;
extern const char *const PRINTF_COLOR_CYAN;
extern const char *const PRINTF_COLOR_RESET;
