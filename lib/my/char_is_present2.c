/*
** EPITECH PROJECT, 2023
** char_is_present_2.c
** File description:
** return 1 if c is present in str
*/

#include "../../include/my.h"

int char_is_present2(char *chars, char *str)
{
    for (int i = 0; chars[i] != '\0'; i++) {
        if (char_is_present(chars[i], str))
            return 1;
    }
    return 0;
}
