/*
** EPITECH PROJECT, 2023
** my_str_to_word_array.c
** File description:
** splits a string into words
*/

#include "../../include/my.h"

static int is_next_to_sep(int i, char const *str, char *a_sep)
{
    char before = '\0';
    char after = str[i + 1];

    if (i > 0)
        before = str[i - 1];
    if (after == '\0')
        return 1;
    for (int i2 = 0; a_sep[i2] != '\0'; i2++) {
        if (after == a_sep[i2] || before == a_sep[i2])
            return 1;
    }
    return 0;
}

static int is_sep2(int i, char const *str, separator_t *seps)
{
    char c = str[i];

    if (c == '\0')
        return 1;
    for (int i2 = 0; seps->separators[i2] != '\0'; i2++) {
        if (c == seps->separators[i2])
            return is_next_to_sep(i, str, seps->next_to_sep);
    }
    return 0;
}

static int num_of_words2(char const *str, int i, separator_t *seps)
{
    int length = my_strlen(str);
    int cpt = 0;

    while (i < length) {
        if (is_sep2(i, str, seps) && !is_sep2(i + 1, str, seps)) {
            cpt++;
        }
        i++;
    }
    return cpt + 1;
}

int *word_length2(char const *str, int num_of_w, int i, separator_t *seps)
{
    int *word_l;
    int cpt = 0;
    int i2 = 0;

    word_l = malloc(sizeof(int) * num_of_w);
    while (i2 < num_of_w) {
        while (!(is_sep2(i, str, seps))) {
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

static char *put_word2(int i3, char const *str, char *word, separator_t *seps)
{
    int i2 = 0;

    while (is_sep2(i3, str, seps))
        i3++;
    while (!(is_sep2(i3, str, seps))) {
            word[i2] = str[i3];
            i3++;
            i2++;
        }
    word[i2] = '\0';
    return word;
}

int begin_spaces2(char const *str, separator_t *seps)
{
    int i = 0;

    while (is_sep2(i, str, seps))
        i++;
    return i;
}

separator_t *set_struct2(char *sep, char *a_sep)
{
    separator_t *seps = malloc(sizeof(separator_t));

    seps->separators = sep;
    seps->next_to_sep = a_sep;
    return seps;
}

char **my_str_to_word_array_2(char const *str, char *sep, char *a_sep)
{
    char *word;
    separator_t *seps = set_struct2(sep, a_sep);
    int i2 = begin_spaces2(str, seps);
    int num_of_w = num_of_words2(str, i2, seps);
    int *word_l = word_length2(str, num_of_w, i2, seps);
    char **result = malloc(sizeof(char *) * (num_of_w + 1));

    for (int i = 0; i < num_of_w; i++) {
        word = malloc(sizeof(char) * (word_l[i]) + 1);
        put_word2(i2, str, word, seps);
        i2 = i2 + word_l[i];
        result[i] = word;
        i2++;
    }
    result[num_of_w] = NULL;
    free(word_l);
    free(seps);
    return result;
}
