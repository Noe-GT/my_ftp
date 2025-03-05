/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** system_utils
*/

#include "../include/ftp.h"

bool directory_exists(const char *path)
{
    struct stat stats;

    stat(path, &stats);
    if (S_ISDIR(stats.st_mode))
        return true;
    return false;
}
