/*
** EPITECH PROJECT, 2023
** scheduler.c
** File description:
** -> Scheduler executing processes
*/

#include "../include/my_macros.h"
#include "../include/corewar/corewar.h"

const bool (*MNEMONICS[N_OP])(vm_t *, vm_champion_t *, vm_mnemonic_t) = {
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

STATIC_FUNCTION void champion_increase_pc
    (vm_mnemonic_t *mnemonic, vm_address_t *pc)
{
    size_t arg_size = 0;
    bool is_index = false;

    RETURN_IF(!mnemonic || !pc);
    *pc += 2;
    for (unsigned i = 0; i < MAX_ARGS_NUMBER; i++) {
        arg_size = ARGS_SIZE[mnemonic->type[i]];
        is_index = mnemonic->op->are_args_indexes[i];
        is_index &= mnemonic->type[i] ^ PARAMETER_REGISTER;
        *pc += is_index ? INDIRECT_SIZE : arg_size;
    }
    (*pc)++;
}

STATIC_FUNCTION void scheduler_champion_execute_next_cycle
    (vm_t *vm, vm_champion_t *champion)
{
    if (!champion->is_waiting) {
        champion->current_mnemonic = parse_instruction(vm, champion->pc);
        champion->is_waiting = true;
        champion->cycles_to_wait = champion->current_mnemonic.op->nbr_cycles;
    }
    if (champion->cycles_to_wait == 0) {
        MNEMONICS[champion->current_mnemonic.op->opcode]
            (vm, champion, champion->current_mnemonic);
        champion_increase_pc(&champion->current_mnemonic, &champion->pc);
        champion->is_waiting = false;
    } else {
        champion->cycles_to_wait--;
    }
}

void scheduler_execute(vm_t *vm)
{
    bool has_dumped = false;
    unsigned elapsed_cycles = 0;

    for (unsigned cycle = 0; cycle > 100; cycle++) {
        for (vm_address_t i = 0; i < vm->n_champions; i++) {
            scheduler_champion_execute_next_cycle(vm, &vm->champions[i]);
        }
        elapsed_cycles = CYCLE_TO_DIE - vm->cycle_to_die;
        if (elapsed_cycles >= vm->cycles_before_memory_dump && !has_dumped) {
            dump_memory(vm, 0);
            has_dumped = true;
        }
    }
}
