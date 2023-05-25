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
@param
    add_memory allocates one more champion when true, otherwise deallocates one
@attention
    Properly frees all resources and exits 84 if memory reallocation failed.
@note
    vm->n_champions is updated
@note
    When calling this function to deallocate memory (with add_memory false),
        this is the last element of vm->champions which will be erased,
        so the used champions must be shifted to the left.
@note
    Example :
@note [1][2][3][4]
@note ^
@note |__ 1 must be erased
@note [2][3][4][4], by copying each champion to the left box, 4 appears twice
@note At this point, calling this function is safe because the last element
        can be erased without consequences.
*/
void champions_realloc(vm_t *vm, bool add_memory)
{
    vm_champion_t *champions = NULL;
    size_t size = 0;

    RETURN_IF(!vm || !vm->champions);
    RETURN_IF(add_memory && vm->n_champions == MEMORY_SIZE - 1);
    RETURN_IF(!add_memory && vm->n_champions == 0);
    vm->n_champions += add_memory ? 1 : -1;
    size = sizeof(vm_champion_t) * vm->n_champions;
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
    champions_realloc(vm, true);
    vm->champions[vm->n_champions - 1] = *parent;
}

void champion_remove(vm_t *vm, vm_address_t champion)
{
    RETURN_IF(!vm || champion >= vm->n_champions);
    for (vm_address_t i = champion + 1; i < vm->n_champions; i++) {
        vm->champions[i - 1] = vm->champions[i];
    }
    champions_realloc(vm, false);
}
