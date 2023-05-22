/*
** EPITECH PROJECT, 2022
** my_put_nbr.c
** File description:
** ->   displays a number (should be reimplemented in a recursive way)
*/

#include <my.h>
#include <my_macros.h>
#include <stdlib.h>

unsigned my_log(long long n)
{
    unsigned log = 0;
    if (n <= 0) {
        return n == 0;
    }
    while (n) {
        n /= 10;
        log++;
    }
    return log;
}

void my_put_nbr(long long n)
{
    if (n < 0) {
        my_putchar('-');
        n = -n;
    }
    const unsigned buf_size = my_log(n);
    char buf[buf_size];
    for (unsigned i = 0; i < buf_size; i++) {
        buf[i] = '0' + n % 10;
        n /= 10;
    }
    for (unsigned i = buf_size - 1; ; i--) {
        my_putchar(buf[i]);
        if (i == 0) {
            break;
        }
    }
}

void my_sput_nbr(long long n, char *buffer)
{
    const unsigned buf_size = my_log(ABS(n));
    unsigned long long power = 1;

    if (n < 0) {
        *buffer++ = '-';
        n = ABS(n);
    }
    while (power <= (unsigned long long)n / 10) {
        power *= 10;
    }
    for (unsigned i = 0; i < buf_size; i++) {
        *buffer++ = '0' + n / power;
        n %= power;
        power /= 10;
    }
}
