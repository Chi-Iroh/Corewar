/*
** EPITECH PROJECT, 2023
** scheduler.c
** File description:
** -> Scheduler executing processes
*/

#include "../include/my_macros.h"
#include "../include/corewar/corewar.h"

bool (*MNEMONICS[N_OP])(vm_t *, vm_champion_t *, vm_mnemonic_t) = {
    [0x01] = mnemonic_live,
    [0x02] = mnemonic_ld,
    [0x03] = mnemonic_st,
    [0x04] = mnemonic_add,
    [0x05] = mnemonic_sub,
    [0x06] = mnemonic_and,
    [0x07] = mnemonic_or,
    [0x08] = mnemonic_xor,
    [0x09] = mnemonic_zjmp,
    [0x0A] = mnemonic_ldi,
    [0x0B] = mnemonic_sti,
    [0x0C] = mnemonic_fork,
    [0x0D] = mnemonic_lld,
    [0x0E] = mnemonic_lldi,
    [0x0F] = mnemonic_lfork,
    [0x10] = mnemonic_aff
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
