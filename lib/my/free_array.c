/*
** EPITECH PROJECT, 2023
** free_array.c
** File description:
** Free an array
*/

#include "my.h"

void free_array(char **array)
{
    int i = 0;

    while (array[i] != NULL) {
        free(array[i]);
        i++;
    }
    free(array[i]);
    free(array);
}
