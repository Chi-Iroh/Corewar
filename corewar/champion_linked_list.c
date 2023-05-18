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
    (vm_champion_list_t **champions_address, vm_champion_t *champion)
{
    vm_champion_list_t *new_node = champions_address && champion ?
        malloc(sizeof(vm_champion_list_t)) : NULL;

    RETURN_VALUE_IF(!new_node, false);
    *new_node = (vm_champion_list_t) {
        .champion = *champion,
        .next = NULL,
        .previous = NULL
    };
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

void champion_free(vm_champion_t *champion_address)
{
    RETURN_IF(!champion_address);
    FREE_IF_ALLOCATED(champion_address->code, fclose);
}

void champions_free(vm_champion_list_t **champions_address)
{
    vm_champion_list_t *next = NULL;

    RETURN_IF(!champions_address);
    while (*champions_address && (*champions_address)->previous) {
        *champions_address = (*champions_address)->previous;
    }
    while (true) {
        next = (*champions_address)->next;
        FREE_CONST_IF_ALLOCATED(&(*champions_address)->champion, champion_free)
        FREE_IF_ALLOCATED(*champions_address, free);
        if (!next) {
            break;
        }
        *champions_address = next;
    }
}
