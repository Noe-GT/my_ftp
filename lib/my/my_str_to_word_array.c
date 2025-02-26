/*
** EPITECH PROJECT, 2023
** my_str_to_word_array.c
** File description:
** splits a string into words
*/

#include "my.h"

static int is_sep(char character, char *sep)
{
    if (character == '\0')
        return 1;
    for (int i = 0; sep[i] != '\0'; i++) {
        if (character == sep[i])
            return 1;
    }
    return 0;
}

static int num_of_words(char const *str, int i, char *sep)
{
    int length = strlen(str);
    int cpt = 0;

    while (i < length) {
        if (is_sep(str[i], sep) && !is_sep(str[i + 1], sep)) {
            cpt++;
        }
        i++;
    }
    return cpt + 1;
}

static int *word_length(char const *str, int num_of_w, int i, char *sep)
{
    int *word_l;
    int cpt = 0;
    int i2 = 0;

    word_l = malloc(sizeof(int) * num_of_w);
    while (i2 < num_of_w) {
        while (!(is_sep(str[i], sep))) {
            cpt++;
            i++;
        }
        word_l[i2] = cpt;
        i2++;
        i++;
        cpt = 0;
    }
    return word_l;
}

static char *put_word(int i3, char const *str, char *word, char *sep)
{
    int i2 = 0;

    while (is_sep(str[i3], sep))
        i3++;
    while (!(is_sep(str[i3], sep))) {
            word[i2] = str[i3];
            i3++;
            i2++;
        }
    word[i2] = '\0';
    return word;
}

int begin_spaces(char const *str, char *sep)
{
    int i = 0;

    while (is_sep(str[i], sep))
        i++;
    return i;
}

char **my_str_to_word_array(char const *str, char *sep)
{
    char *word;
    int i = 0;
    int i2 = begin_spaces(str, sep);
    int num_of_w = num_of_words(str, i2, sep);
    int *word_l = word_length(str, num_of_w, i2, sep);
    char **result = malloc(sizeof(char *) * (num_of_w + 1));

    while (i < num_of_w) {
        word = malloc(sizeof(char) * (word_l[i]) + 1);
        put_word(i2, str, word, sep);
        i2 = i2 + word_l[i];
        result[i] = malloc(sizeof(char) * word_l[i] + 1);
        result[i] = word;
        i++;
        i2++;
    }
    result[i] = NULL;
    return result;
}
