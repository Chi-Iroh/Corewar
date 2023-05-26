/*
** EPITECH PROJECT, 2023
** tests_my_memcpy.c
** File description:
** -> Tests for my_memcpy function
*/

#include "../../include/corewar/corewar.h"
#include <criterion/criterion.h>

Test(my_memcpy, my_memcpy) {
    unsigned char array[11] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    unsigned char str[11] = "Helloworld";

    my_memcpy(&array[0], &str[0], 11);
    for (unsigned i = 0; i < 11; i++) {
        cr_expect(array[i] == str[i], "%uth byte isn't the same (%hhu expected, %hhu given)", i, str[i], array[i]);
    }
}
