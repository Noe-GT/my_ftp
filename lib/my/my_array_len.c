/*
** EPITECH PROJECT, 2025
** libmy
** File description:
** my_array_len
*/

#include "my.h"

int my_array_len(char **array)
{
    int count = 0;

    while (array[count] != NULL)
        count++;
    return count;
}
