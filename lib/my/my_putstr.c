/*
** EPITECH PROJECT, 2023
** my_putstr.c
** File description:
** displays, one-by-one, the characters of a string
*/

#include <unistd.h>
#include <stdio.h>
#include "my.h"

int my_putstr(char const *str)
{
    int count = 0;

    while (str[count] != '\0') {
        my_putchar(str[count]);
        count++;
    }
    return count;
}
