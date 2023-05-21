/*
** EPITECH PROJECT, 2023
** prog_number.c
** File description:
** -> Prog number utilities
*/

#include <stdlib.h>
#include "../include/my.h"
#include "../include/my_macros.h"
#include "../include/corewar/corewar.h"

/*
@brief
    Swaps *a and *b if *a is greater than *b.
@param
    a is the first value
@param
    b is the second value
@note
    XOR swap implementation
*/
STATIC_FUNCTION void swap_if_greater(vm_address_t *a, vm_address_t *b)
{
    if (*a > *b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

/*
@brief
    Checks the next prog number not used by any champion.
@param
    used is the array of used prog numbers
@param
    size is the number of elements in array
@returns
    the lowest number not in used
@note
    size must be lower then VM_ADDRESS_MAX to have at least one usable number
*/
STATIC_FUNCTION vm_address_t champions_next_prog_number_impl
    (vm_address_t *used, unsigned size)
{
    vm_address_t n = 0;

    for (unsigned i = 0; i < size; i++) {
        for (unsigned j = i; j < size - 1; j++) {
            swap_if_greater(&used[i], &used[i + 1]);
        }
    }
    for (vm_address_t i = 0; used[i] == n && i < size; i++) {
        n++;
    }
    return n;
}

/*
@brief
    Checks the next prog number not used by any champion.
@param
    vm is the Virtual Machine
@param
    prog_number is where to store the next usable prog number
@returns
    true if there's an usable number, false otherwise or on error
*/
bool champions_next_prog_number
    (vm_t *vm, vm_address_t *prog_number)
{
    vm_address_t *used = prog_number ?
        malloc(sizeof(vm_address_t) * vm->n_champions) : NULL;
    bool status = vm->n_champions < VM_ADDRESS_MAX;

    *prog_number = 0;
    RETURN_VALUE_IF(vm && !vm->champions, status);
    RETURN_VALUE_IF(!status || !used, false);
    for (vm_address_t i = 0; i < vm->n_champions; i++) {
        used[i] = vm->champions[i].number;
    }
    *prog_number = champions_next_prog_number_impl(used, vm->n_champions);
    free(used);
    return status;
}

/*
@brief
    Checks is a prog number is used by a champion or not.
@param
    vm is the Virtual Machine
@param
    prog_number is the number to search
@returns
    true if prog_number is used by a champion, false otherwise
*/
bool champions_has_prog_number
    (vm_t *vm, vm_address_t prog_number)
{
    for (vm_address_t i = 0; i < vm->n_champions; i++) {
        RETURN_VALUE_IF(vm->champions[i].number == prog_number, true);
    }
    return false;
}
