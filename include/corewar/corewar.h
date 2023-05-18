/*
** EPITECH PROJECT, 2023
** corewar.h
** File description:
** -> Header for VM part
*/

#pragma once

#include <limits.h>
#include <stdint.h>
#include "corewar_config.h"
#include "../op.h"

#if REGISTER_SIZE == 1
    typedef uint8_t register_t;
#elif REGISTER_SIZE == 2
    typedef uint16_t register_t;
#elif REGISTER_SIZE == 4
    typedef uint32_t register_t;
#elif REGISTER_SIZE == 8
    typedef uint64_t register_t;
#else
    #error "REGISTER_SIZE not 1, 2, 4 or 8 !"
#endif

#if MEM_SIZE <= UINT8_MAX
    typedef uint8_t address_t;
#elif MEM_SIZE <= UINT16_MAX
    typedef uint16_t address_t;
#elif MEM_SIZE <= UINT32_MAX
    typedef uint32_t address_t;
#else
    typedef uint64_t address_t;
#endif

typedef enum {
    CARRY_ON,
    CARRY_OFF
} carry_t;

typedef uint8_t memory_t[MEMORY_SIZE];

typedef struct {
    register_t registers[REGISTERS_NUMBER];
    carry_t carry;
    unsigned number;
} champion_t;
