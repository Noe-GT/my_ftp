/*
** EPITECH PROJECT, 2023
** char_is_present.c
** File description:
** return 1 if c is present in str
*/

#include "../../include/my.h"

int char_is_present(char c, char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (c == str[i])
            return 1;
    }
    return 0;
}
