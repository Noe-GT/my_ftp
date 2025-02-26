/*
** EPITECH PROJECT, 2023
** clean_str.c
** File description:
** removes unwanted characters
*/

#include "my.h"

int is_unwanted2(char *str, char *unwanted, int pos)
{
    for (int i = 0; unwanted[i] != '\0'; i++) {
        if (str[pos] == unwanted[i])
            return 1;
    }
    return 0;
}

int before_len(char *str, char *unwanted)
{
    int count = 0;

    while (is_unwanted2(str, unwanted, count)) {
        count++;
    }
    return count;
}

int after_len(char *str, char *unwanted, int i)
{
    int count = 0;

    while (is_unwanted2(str, unwanted, i)) {
        i--;
        count++;
    }
    return count;
}

char *clean_str_ba(char *str, char *unwanted)
{
    int pos = 0;
    char *result;
    int total_len = strlen(str);
    int b_len = before_len(str, unwanted);
    int a_len = after_len(str, unwanted, total_len - 1);
    int result_len = total_len - b_len - a_len;

    result = malloc(sizeof(char) * result_len + 1);
    for (int i2 = b_len; i2 < total_len - a_len; i2++) {
        result[pos] = str[i2];
        pos++;
    }
    result[result_len] = '\0';
    return result;
}
