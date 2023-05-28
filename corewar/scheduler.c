/*
** EPITECH PROJECT, 2023
** scheduler.c
** File description:
** -> Scheduler executing processes
*/

#include "../include/my_macros.h"
#include "../include/corewar/corewar.h"

bool (*const MNEMONICS[MNEMONIC_MAX])
    (vm_t *, vm_champion_t *, vm_mnemonic_t) = {
    [MNEMONIC_LIVE] = mnemonic_live,
    [MNEMONIC_LD] = mnemonic_ld,
    [MNEMONIC_ST] = mnemonic_st,
    [MNEMONIC_ADD] = mnemonic_add,
    [MNEMONIC_SUB] = mnemonic_sub,
    [MNEMONIC_AND] = mnemonic_and,
    [MNEMONIC_OR] = mnemonic_or,
    [MNEMONIC_XOR] = mnemonic_xor,
    [MNEMONIC_ZJMP] = mnemonic_zjmp,
    [MNEMONIC_LDI] = mnemonic_ldi,
    [MNEMONIC_STI] = mnemonic_sti,
    [MNEMONIC_FORK] = mnemonic_fork,
    [MNEMONIC_LLD] = mnemonic_lld,
    [MNEMONIC_LLDI] = mnemonic_lldi,
    [MNEMONIC_LFORK] = mnemonic_lfork,
    [MNEMONIC_AFF] = mnemonic_aff
};

/*
@brief
    Increases the program counter of a champion, according to its current
        instruction.
@param
    champion is the champion to change the program counter
@note
    Does nothing if champion is NULL.
*/
STATIC_FUNCTION void champion_increase_pc
    (vm_champion_t *champion)
{
    size_t arg_size = 0;
    bool is_index = false;

    RETURN_IF(!champion);
    champion->pc += 2;
    champion->pc %= MEMORY_SIZE;
    for (unsigned i = 0; i < MAX_ARGS_NUMBER; i++) {
        arg_size = ARG_SIZE[champion->current_mnemonic.type[i]];
        is_index = champion->current_mnemonic.op->are_args_indexes[i];
        is_index &= champion->current_mnemonic.type[i] != PARAMETER_REGISTER;
        champion->pc += is_index ? INDIRECT_SIZE : arg_size;
        champion->pc %= MEMORY_SIZE;
    }
    champion->pc++;
    champion->pc %= MEMORY_SIZE;
}

/*
@brief
    Executes the next cycle, waits before executing an instruction.
@param
    vm is the Virtual Machine
@param
    champion is the champion to execute the next cycle
@note
    Does nothing if champion or vm is NULL.
*/
STATIC_FUNCTION void scheduler_champion_execute_next_cycle
    (vm_t *vm, vm_champion_t *champion)
{
    RETURN_IF(!vm || !champion);
    if (!champion->is_waiting) {
        champion->current_mnemonic = parse_instruction(vm, champion->pc);
        champion->is_waiting = true;
        champion->cycles_to_wait = champion->current_mnemonic.op->nbr_cycles;
    }
    if (champion->cycles_to_wait == 0) {
        MNEMONICS[champion->current_mnemonic.op->opcode]
            (vm, champion, champion->current_mnemonic);
        champion_increase_pc(champion);
        champion->is_waiting = false;
    } else {
        champion->cycles_to_wait--;
    }
}

/*
@brief
    Removes a dead program.
@param
    vm is the Virtual Machine
@param
    index points to the program index to remove
@note
    Does nothing if vm or index is NULL.
@attention
    If champions reallocation fails, properly frees resources and exits with
        code 84.
*/
STATIC_FUNCTION void scheduler_remove_program(vm_t *vm, unsigned *index)
{
    const bool is_index_ok = index ? *index < UINT_MAX && *index > 0 : false;

    RETURN_IF(!vm || !index);
    for (unsigned i = *index + 1; i < vm->n_champions && is_index_ok; i++) {
        vm->champions[i - 1] = vm->champions[i];
    }
    champions_realloc(vm, false);
    (*index)--;
}

/*
@brief
    Removes all dead programs in Virtual Machine.
@param
    vm is the Virtual Machine
@note
    Does nothing if vm is NULL.
@attention
    If champions reallocation fails, properly frees resources and exits with
        code 84.
*/
STATIC_FUNCTION void scheduler_remove_dead_programs(vm_t *vm)
{
    RETURN_IF(!vm);
    for (unsigned i = 0; i < vm->n_champions; i++) {
        if (!vm->champions[i].is_alive) {
            scheduler_remove_program(vm, &i);
        }
        vm->champions[i].cycles_to_wait = 0;
        vm->champions[i].is_waiting = false;
    }
}

/*
@brief
    Executes all the instructions in the Virtual Machine.
@param
    vm is the Virtual Machine
@note
    Does nothing if vm is NULL.
@attention
    If champions reallocation fails, properly frees resources and exits with
        code 84.
*/
void scheduler_execute(vm_t *vm)
{
    bool has_dumped = false;
    unsigned global_cycle = 0;

    RETURN_IF(!vm);
    for (unsigned cycle = 0; vm->n_champions > 0; cycle++, global_cycle++) {
        if (vm->n_lives >= NBR_LIVE) {
            vm->cycle_to_die -= CYCLE_DELTA;
            vm->n_lives = 0;
        }
        if (cycle == vm->cycle_to_die) {
            scheduler_remove_dead_programs(vm);
            cycle = 0;
        }
        for (vm_address_t i = 0; i < vm->n_champions; i++) {
            scheduler_champion_execute_next_cycle(vm, &vm->champions[i]);
        }
        if (!has_dumped && global_cycle >= vm->cycles_before_memory_dump) {
            dump_memory(vm, 0);
            has_dumped = true;
        }
    }
}
