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
