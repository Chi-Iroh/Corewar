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
    (vm_champion_list_t **champions_address, vm_champion_t *champion);

void champion_free(vm_champion_t *champion_address);
void champions_free(vm_champion_list_t **champions_address);
