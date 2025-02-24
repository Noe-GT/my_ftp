/*
** EPITECH PROJECT, 2023
** my_putstr_error.c
** File description:
** displays, one-by-one, the characters of a string
*/

#include <unistd.h>
#include <stdio.h>
#include "my.h"

int my_putstr_error(char const *str)
{
    int count = 0;

    while (str[count] != '\0') {
        write(2, &str[count], 1);
        count++;
    }
    return count;
}
