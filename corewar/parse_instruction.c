/*
** EPITECH PROJECT, 2023
** parse_instruction.c
** File description:
** -> Parses a binary instruction
*/

#include "../include/my_macros.h"
#include "../include/corewar/corewar.h"

// Byte coding of each parameter type (00 = PARAMETER_MAX = no parameter)
const mnemonic_parameter_t ARGS_BITS_TO_NAME[1 << PARAMETER_TYPE_BITS] = {
    [0b00] = PARAMETER_MAX,
    [0b01] = PARAMETER_REGISTER,
    [0b10] = PARAMETER_DIRECT,
    [0b11] = PARAMETER_INDIRECT
};

const unsigned ARGS_NAME_TO_BITS[PARAMETER_MAX + 1] = {
    [PARAMETER_MAX] = 0b00,
    [PARAMETER_REGISTER] = 0b01,
    [PARAMETER_DIRECT] = 0b10,
    [PARAMETER_INDIRECT] = 0b11
};

// Size of each parameter type
const unsigned ARGS_SIZE[PARAMETER_MAX + 1] = {
    [PARAMETER_DIRECT] = DIRECT_SIZE,
    [PARAMETER_INDIRECT] = INDIRECT_SIZE,
    [PARAMETER_REGISTER] = REGISTER_SIZE,
};

/*
@brief
    Reads op_tab and gets the instruction name (live, add etc..) corresponding
        to an opcode.
@param
    opcode is the înstruction code
@returns
    NULL is the opcode doesn't match to any instruction, otherwise a static
        string whoch is the instruction name.
*/
STATIC_FUNCTION char *mnemonic_get_from_opcode(uint8_t opcode)
{
    for (unsigned i = 0; i < LAST_OP; i++) {
        if (op_tab[i].opcode == opcode) {
            return op_tab[i].mnemonic;
        }
    }
    return NULL;
}

/*
@brief
    Reads instruction argument, a given number of bytes in the memory.
@param
    vm is the Virtual Machine
@param
    address is the address to read from in the memory
@param
    n_bytes is the number of bytes to read
@param
    arg is where to store the read bytes
@returns
    true on success, false on failure
*/
STATIC_FUNCTION bool mnemonic_arg_read_n_bytes
    (vm_t *vm, vm_address_t *address, vm_address_t n_bytes, uintmax_t *arg)
{
    RETURN_VALUE_IF(!vm || !address || !arg, false);
    RETURN_VALUE_IF(n_bytes >= MEMORY_SIZE, false);
    RETURN_VALUE_IF(*address >= MEMORY_SIZE - n_bytes, false);
    *arg = 0;
    for (vm_address_t i = 0; i < n_bytes; i++) {
        *arg <<= 8;
        *arg |= vm->memory[*address + i];
    }
    return true;
}

/*
@brief
    Parses the memory to get mnemonic args.
@param
    vm is the Virtual Machine
@param
    address is the address of the args in memory
@param
    mnemonic is the mnemonic to read the args (only contains types initialized)
@returns
    true on success, false on failure
*/
STATIC_FUNCTION bool mnemonic_get_args
    (vm_t *vm, vm_address_t address, vm_mnemonic_t *mnemonic)
{
    unsigned arg_size = 0;
    uintmax_t *arg = NULL;

    for (unsigned i = 0; i < MAX_ARGS_NUMBER; i++) {
        RETURN_VALUE_IF(address >= MEMORY_SIZE, false);
        RETURN_VALUE_IF(mnemonic->type[i] == PARAMETER_MAX, true);
        arg_size = ARGS_SIZE[mnemonic->type[i]];
        arg = &mnemonic->args[i];
        if (!mnemonic_arg_read_n_bytes(vm, &address, arg_size, arg)) {
            return false;
        }
        address += arg_size;
    }
    return true;
}

/*
@brief
    Parses a binary instruction.
@returns
    a structure containing the mnemonic and its parameters
@param
    vm is the vm structure
@param
    address is the address from where to read
@note
    On error, the returned structure has the mnemonic member set to NULL.
*/
vm_mnemonic_t parse_instruction(vm_t *vm, vm_address_t address)
{
    static const vm_mnemonic_t error = { .mnemonic = NULL };
    vm_mnemonic_t mnemonic = {};

    RETURN_VALUE_IF(!vm, error);
    mnemonic.mnemonic = mnemonic_get_from_opcode(vm->memory[address++]);
    RETURN_VALUE_IF(!mnemonic.mnemonic, error);
    mnemonic.type[0] = ARGS_BITS_TO_NAME[(vm->memory[address] & 0xC0) >> 6];
    mnemonic.type[1] = ARGS_BITS_TO_NAME[(vm->memory[address] & 0x30) >> 4];
    mnemonic.type[2] = ARGS_BITS_TO_NAME[(vm->memory[address] & 0x0C) >> 2];
    mnemonic.type[3] = ARGS_BITS_TO_NAME[(vm->memory[address++] & 0x03)];
    return mnemonic_get_args(vm, address, &mnemonic) ? mnemonic : error;
}
