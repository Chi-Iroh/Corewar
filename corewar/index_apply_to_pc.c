/*
** EPITECH PROJECT, 2023
** index_apply_to_pc.c
** File description:
** -> Applies an index arg to a champion's program counter
*/

#include "../include/my_macros.h"
#include "../include/corewar/corewar.h"

/*
@brief
    Applies an index to a champion pc (see note), correctly decoding it.
@param
    pc is the program counter (MUST be in [0;MEMORY_SIZE - 1], no check here)
@param
    index is the index value to apply
@param
    apply_index_modulo is a switch to apply or not a modulo INDEX_MODULO
        on the index
@returns
    MEMORY_SIZE on error,
        otherwise pc +/- abs(index) [eventually % INDEX_MODULO]
*/
vm_address_t index_apply_to_pc
    (vm_address_t pc, vm_indirect_arg_t index, bool apply_index_modulo)
{
    vm_address_t index_abs = index > MEMORY_SIZE ? 0x01'00'00 - index : index;
    const vm_address_t pc_distance_from_end = MEMORY_SIZE - pc - 1;

    index = apply_index_modulo ? index % INDEX_MODULO : index;
    if (index < MEMORY_SIZE) {
        if (index_abs > pc_distance_from_end) {
            pc = index_abs - pc_distance_from_end;
        } else {
            pc += index_abs;
        }
    } else {
        if (index_abs > pc) {
            pc = index_abs - pc;
        } else {
            pc -= index_abs;
        }
    }
    return pc;
}
