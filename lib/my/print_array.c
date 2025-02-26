/*
** EPITECH PROJECT, 2023
** nbr_to_str
** File description:
** nbr_to_str
*/

#include "my.h"

void print_array(char **array)
{
    while (*array) {
        puts(*array);
        array++;
        putchar('\n');
    }
}
