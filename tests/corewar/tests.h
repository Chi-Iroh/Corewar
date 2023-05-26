/*
** EPITECH PROJECT, 2023
** tests.h
** File description:
** -> Proto for tests
*/

#pragma once
#include <memory.h>
#include "../../include/corewar/corewar.h"

#define VM_INDEX(x) ((x) < 0 ? 0x1'00'00 - -(x) : (x))

// mnemonic is not a pointer but a copy because this function is destructive
void write_instruction(vm_t *vm, vm_mnemonic_t mnemonic, vm_address_t address, bool zero_init_all_memory);
