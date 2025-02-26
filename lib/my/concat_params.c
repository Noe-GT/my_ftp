/*
** EPITECH PROJECT, 2023
** C-pool
** File description:
** concat_params
*/

#include "my.h"

char *concat_params(int argc, char **argv)
{
    int max_len = 0;
    char *str = 0;
    int l = 0;
    int ln = 0;

    for (int i = 0; i < argc; i++){
        max_len += strlen(argv[i]) + 1;
    }
    str = (char *)malloc((max_len + 1) * sizeof(char) + argc);
    for (int j = 0; j < argc; j++){
        ln = strlen(argv[j]);
        for (int k = 0; k < ln; k++){
            str[l] = argv[j][k];
            l++;
        }
        str[l] = '\n';
        l++;
    }
    str[max_len] = '\0';
    return str;
}
