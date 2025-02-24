/*
** EPITECH PROJECT, 2023
** str_cut
** File description:
** str_cut
*/

#include "../../include/my.h"

char *str_cut(char *str, int pos)
{
    int len = my_strlen(str);
    int i = pos + 1;
    char *result = malloc(sizeof(char) * (len - pos + 1));

    while (i < len) {
        result[i - pos - 1] = str[i];
        i++;
    }
    result[i - pos - 1] = '\0';
    return result;
}
