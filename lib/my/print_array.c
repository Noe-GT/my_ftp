/*
** EPITECH PROJECT, 2023
** nbr_to_str
** File description:
** nbr_to_str
*/

#include "my.h"

void print_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        printf("%d: %s\n", i, array[i]);
}
