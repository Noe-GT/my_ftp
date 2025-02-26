/*
** EPITECH PROJECT, 2025
** libmy
** File description:
** Adds element to the end of an int array of size <arr_size>
*/

#include "my.h"

int *add_to_int_array(int *array, int new_elem, int arr_size)
{
    int *temp = (int *)malloc(sizeof(int) * (arr_size + 1));
    int ti = 0;

    for (int si = 0; si < arr_size; si++) {
        temp[ti] = array[si];
        ti++;
    }
    temp[ti] = new_elem;
    free(array);
    return temp;
}
