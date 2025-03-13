/*
** EPITECH PROJECT, 2025
** mylib
** File description:
** str_to_array
*/

#include "my.h"

static bool char_in_str(char *str, char c)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (c == str[i])
            return true;
    }
    return false;
}

static int count_sep(char *str, char *sep)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (char_in_str(sep, str[i]))
            count++;
    }
    return count;
}

char **str_to_array(char *str, char *sep)
{
    int len = count_sep(str, sep) + 1;
    char *parse = strtok(str, sep);
    char **array = (char **)malloc(sizeof(char *) * (len + 1));

    printf("len: %d\n", len);
    for (int i = 0; parse != NULL; i++) {
        array[i] = strdup(parse);
        parse = strtok(NULL, sep);
    }
    array[len] = NULL;
    return array;
}
