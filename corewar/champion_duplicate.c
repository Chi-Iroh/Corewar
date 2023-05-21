/*
** EPITECH PROJECT, 2023
** champions_realloc.c
** File description:
** -> Properly realloc champions
*/

#include <stdlib.h>
#include "../include/my_macros.h"
#include "../include/corewar/corewar.h"

/*
@brief
    Allocates memory for one more champion, and default-initializes it.
@param
    vm is the Virtual Machine
@note
    Properly frees all resources and exits 84 if memory reallocation failed.
*/
STATIC_FUNCTION void champions_realloc(vm_t *vm)
{
    vm_champion_t *champions = NULL;
    size_t size = 0;

    RETURN_IF(!vm || !vm->champions);
    size = sizeof(vm_champion_t) * ++vm->n_champions;
    champions = realloc(vm->champions, size);
    if (!champions) {
        free(vm->champions);
        exit(84);
    }
    vm->champions = champions;
    vm->champions[vm->n_champions - 1] = CHAMPION_DEFAULT;
}

/*
@brief
    Duplicates a champion (used by fork and lfork instruction).
@param
    vm is the Virtual Machine
@param
    number is the number of the program that must be duplicated
@note
    Properly frees all resources and exits 84 if memory reallocation failed.
@note
    The duplicated champion has the same number as its parent.
@note
    Does nothing if either vm or parent pointer is NULL.
*/
void champion_duplicate(vm_t *vm, vm_champion_t *parent)
{
    RETURN_IF(!vm || !parent);
    champions_realloc(vm);
    vm->champions[vm->n_champions - 1] = *parent;
}
