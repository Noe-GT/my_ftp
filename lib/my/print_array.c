/*
** EPITECH PROJECT, 2023
** nbr_to_str
** File description:
** nbr_to_str
*/

#include "../../include/my.h"

void print_array(char **array)
{
    while (*array) {
        my_putstr(*array);
        array++;
        my_putchar('\n');
    }
}
