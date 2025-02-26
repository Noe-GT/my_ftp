/*
** EPITECH PROJECT, 2023
** my_show_word_array
** File description:
** my_show_word_array
*/


#include "my.h"

int nbr_str(char *const *tab)
{
    int i = 0;

    while (tab[i] != 0){
        i++;
    }
    return i;
}

int my_show_word_array(char *const *tab)
{
    int len = 0;
    int nbr = nbr_str(tab);
    int i = 0;

    while (i < nbr) {
        len = strlen(tab[i]);
        write(1, tab[i], len);
        putchar('\n');
        i++;
    }
    return i;
}
