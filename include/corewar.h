/*
** EPITECH PROJECT, 2023
** corewar.h
** File description:
** -> Header for VM part
*/

#pragma once

#include <limits.h>
#include <stdint.h>
#include "op.h"

#if REG_SIZE == 1
    typedef uint8_t register_t;
#elif REG_SIZE == 2
    typedef uint16_t register_t;
#elif REG_SIZE == 4
    typedef uint32_t register_t;
#elif REG_SIZE == 8
    typedef uint64_t register_t;
#else
    #error "REG_SIZE not 1, 2, 4 or 8 !"
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

typedef struct {
    register_t registers[REG_NUMBER];
    uint8_t memory[MEM_SIZE];
    carry_t carry;
} cpu_t;
