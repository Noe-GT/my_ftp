/*
** EPITECH PROJECT, 2025
** libmy
** File description:
** print_int_array
*/

#include "my.h"

void print_int_array(int *array, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d\n", array[i]);
}
