/*
** EPITECH PROJECT, 2023
** champion_linked_list.c
** File description:
** -> Champion linked list utilities.
*/
#include <stdlib.h>
#include <stdio.h>
#include "../include/my_macros.h"
#include "../include/corewar/corewar.h"

bool champion_add
    (vm_champion_t **champions_address, vm_champion_t *champion_address)
{
    vm_champion_t *new_node = champions_address && champion_address ?
        malloc(sizeof(vm_champion_t)) : NULL;

    RETURN_VALUE_IF(!new_node, false);
    *new_node = *champion_address;
    while (*champions_address && (*champions_address)->next) {
        *champions_address = (*champions_address)->next;
    }
    if (!(*champions_address)) {
        *champions_address = new_node;
    } else {
        new_node->previous = *champions_address;
        (*champions_address)->next = new_node;
    }
    return true;
}

void champion_free_node(vm_champion_t *champion_node)
{
    if (champion_node) {
        free(champion_node);
    }
}

void champions_free(vm_champion_t **champions_address)
{
    vm_champion_t *next = NULL;

    RETURN_IF(!champions_address);
    while (*champions_address && (*champions_address)->previous) {
        *champions_address = (*champions_address)->previous;
    }
    while (*champions_address) {
        next = (*champions_address)->next;
        FREE_IF_ALLOCATED(*champions_address, champion_free_node);
        if (!next) {
            break;
        }
        *champions_address = next;
    }
}
