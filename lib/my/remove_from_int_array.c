/*
** EPITECH PROJECT, 2025
** libmy
** File description:
** removes elem at position <elemi> from a int array of size <arr_size>
*/

#include "my.h"

int *remove_from_int_array(int *array, int elemi, int arr_size)
{
    int *temp = (int *)malloc(sizeof(int) * arr_size - 1);
    int ti = 0;

    for (int si = 0; si < arr_size; si++) {
        if (si == elemi)
            si++;
        if (si != arr_size) {
            temp[ti] = array[si];
            ti++;
        }
    }
    free(array);
    return temp;
}
