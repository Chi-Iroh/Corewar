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

bool champion_add
    (vm_champion_t **champions_address, vm_champion_t *champion);

void champion_free_struct(vm_champion_t *champion_address);
void champion_free_node(vm_champion_t *champion_node);
void champions_free(vm_champion_t **champions_address);

uintmax_t mnemonic_get_arg
    (vm_mnemonic_args_t args, unsigned index, vm_champion_t *champion);
uintmax_t mnemonic_get_indirect_address_value
    (vm_t *vm, asm_parameter_t type, uintmax_t value);

void my_memcpy(void *destination, void *source, size_t size);

bool mnemonic_are_args_ok(char *mnemonic, vm_mnemonic_args_t args);
bool mnemonic_ld(vm_t *vm, vm_champion_t *champion, vm_mnemonic_args_t args);
bool mnemonic_st(vm_t *vm, vm_champion_t *champion, vm_mnemonic_args_t args);
bool mnemonic_add(vm_t *vm, vm_champion_t *champion, vm_mnemonic_args_t args);
bool mnemonic_sub(vm_t *vm, vm_champion_t *champion, vm_mnemonic_args_t args);
bool mnemonic_and(vm_t *vm, vm_champion_t *champion, vm_mnemonic_args_t args);
bool mnemonic_or(vm_t *vm, vm_champion_t *champion, vm_mnemonic_args_t args);
