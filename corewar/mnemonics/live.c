/*
** EPITECH PROJECT, 2023
** live.c
** File description:
** -> live mnemonic
*/

#include "../../include/my.h"
#include "../../include/my_macros.h"
#include "../../include/corewar/corewar.h"

void print_champion_name(vm_champion_t *champion)
{
    char *str = my_strrchr(champion->filename, '/');
    char *const dot = my_strrchr(champion->filename, '.');

    if (!str) {
        str = champion->filename;
    } else {
        str++;
    }
    while (str != dot) {
        my_putchar(*str++);
    }
}

/*
@brief
    LIVE mnemonic : indicates that a champion is still alive.
@param
    vm is the Virtual Machine
@param
    champion is the champion who executed the instruction
@param
    args are the arguments types and values
@returns
    true on success, false on failure
@note
    Doesn't change the carry.
*/
bool mnemonic_live(vm_t *vm, vm_champion_t *champion, vm_mnemonic_t args)
{
    uintmax_t arg1 = 0;

    RETURN_VALUE_IF(!vm || !champion, false);
    RETURN_VALUE_IF(!mnemonic_are_args_ok(args), false);
    arg1 = mnemonic_get_arg(args, 0, champion);
    for (vm_address_t i = 0; i < vm->n_champions; i++) {
        if (vm->champions[i].number == arg1) {
            vm->champions[i].is_alive = true;
            vm->n_lives++;
            vm->last_process_alive = arg1;
            break;
        }
    }
    my_printf("The player %u(", champion->number);
    print_champion_name(champion);
    my_puts(")is alive.");
    return true;
}
