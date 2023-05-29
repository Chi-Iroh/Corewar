/*
** EPITECH PROJECT, 2023
** vm_init.c
** File description:
** -> Initializes the Virtual Machine
*/

#include <stdlib.h>
#include "../include/my_macros.h"
#include "../include/corewar/corewar.h"

const vm_champion_t CHAMPION_DEFAULT = {
    .carry = CARRY_OFF,
    .cycles_to_wait = 0,
    .current_mnemonic = {},
    .filename = NULL,
    .is_waiting = false,
    .load_address = VM_ADDRESS_MAX,
    .number = 1,
    .pc = 0,
    .registers = {},
    .size = 0,
};

/*
@brief
    Counts how many champions there are in argv.
@param
    argv are the command line arguments
@returns
    the number of champions in argv
@note
    argv syntax MUST be valid when calling this function.
*/
STATIC_FUNCTION unsigned binary_argv_count_champions(char *argv[])
{
    vm_address_t n_champions = 0;

    for (unsigned i = 1; argv && argv[i]; i++) {
        if (parse_argv_is_flag(argv[i])) {
            continue;
        }
        n_champions++;
    }
    return n_champions;
}

/*
@brief
    Initializes a Virtual Machine.
@param
    vm is the Virtual Machine.
@param
    argv are the command line arguments.
@returns
    false on error, true otherwise.
*/
bool vm_init(vm_t *vm, char *argv[])
{
    RETURN_VALUE_IF(!vm, false);
    *vm = (vm_t) {
        .memory = {},
        .n_champions = binary_argv_count_champions(argv),
        .champions = NULL,
        .must_dump_memory = false,
        .cycles_before_memory_dump = 0,
        .cycle_to_die = CYCLE_TO_DIE,
        .last_process_alive = VM_ADDRESS_MAX
    };
    if (vm->n_champions > 0) {
        vm->champions = malloc(sizeof(vm_champion_t) * vm->n_champions);
    }
    for (unsigned i = 0; vm->champions && i < vm->n_champions; i++) {
        vm->champions[i] = CHAMPION_DEFAULT;
    }
    return vm->champions != NULL;
}
