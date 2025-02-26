/*
** EPITECH PROJECT, 2023
** clean_str.c
** File description:
** removes unwanted spaces
*/

#include "my.h"

char *remove_unwanted_spaces(char *str)
{
    int length = 0;
    int pos = 0;
    char *result;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!(str[i] == ' ' && str[i + 1] == ' '))
            length++;
    }
    result = malloc(sizeof(char) * length + 1);
    for (int i2 = 0; str[i2] != '\0'; i2++) {
        if (!(str[i2] == ' ' && str[i2 + 1] == ' ')) {
            result[pos] = str[i2];
            pos++;
        }
    }
    result[length] = '\0';
    return result;
}
