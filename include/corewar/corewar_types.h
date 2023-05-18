/*
** EPITECH PROJECT, 2023
** corewar.h
** File description:
** -> Header for VM part
*/

#pragma once

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include "corewar_config.h"
#include "../op.h"

// register_t is already a typedef in sys/types.h
// (POSIX standard states every typedef ending with _t may not be reserved)
#if REGISTER_SIZE == 1
    typedef uint8_t vm_register_t;
#elif REGISTER_SIZE == 2
    typedef uint16_t vm_register_t;
#elif REGISTER_SIZE == 4
    typedef uint32_t vm_register_t;
#elif REGISTER_SIZE == 8
    typedef uint64_t vm_register_t;
#else
    #error "REGISTER_SIZE not 1, 2, 4 or 8 !"
#endif

#if MEMORY_SIZE <= UINT8_MAX
    typedef uint8_t vm_address_t;
#elif MEMORY_SIZE <= UINT16_MAX
    typedef uint16_t vm_address_t;
#elif MEMORY_SIZE <= UINT32_MAX
    typedef uint32_t vm_address_t;
#else
    typedef uint64_t vm_address_t;
#endif

typedef enum {
    CARRY_ON,
    CARRY_OFF
} vm_carry_t;

typedef uint8_t vm_memory_t[MEMORY_SIZE];

typedef struct {
    vm_register_t registers[REGISTERS_NUMBER];
    vm_carry_t carry;
    unsigned number;
    uintmax_t pc;
    FILE *code;
} vm_champion_t;

typedef struct vm_champion_list_s {
    struct vm_champion_list_s *previous;
    struct vm_champion_list_s *next;
    vm_champion_t champion;
} vm_champion_list_t;

typedef struct {
    vm_memory_t memory;
    vm_champion_list_t *champions;
} vm_t;
