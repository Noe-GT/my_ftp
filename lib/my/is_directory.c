/*
** EPITECH PROJECT, 2025
** myLib
** File description:
** is_directory
*/

#include "my.h"

int is_directory(const char *path)
{
    struct stat statbuf;

    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}
