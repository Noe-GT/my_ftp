/*
** EPITECH PROJECT, 2025
** libmy
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdbool.h>
    #include <dirent.h>
    #include <sys/stat.h>

int my_show_word_array(char *const *tab);
int nbr_str(char *const *tab);
char *concat_params(int argc, char **argv);
char **my_str_to_word_array(char const *str, char *sep);
void print_array(char **array);
void print_int_array(int *array, int size);
void free_array(char **array);
char *clean_str(char *str, char *unwanted);
char *clean_str_ba(char *str, char *unwanted);
char *str_cut(char *str, int pos);
char *remove_unwanted_spaces(char *str);
int char_is_present(char c, char *str);
int char_is_present2(char *chars, char *str);
int my_array_len(char **array);
int *remove_from_int_array(int *array, int elemi, int arr_size);
int *add_to_int_array(int *array, int new_elem, int arr_size);
char **str_to_array(char *str, char *sep);
int is_directory(const char *path);
int disp_files(const char *path, int fd);

#endif
