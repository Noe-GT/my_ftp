/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** path_handling
*/

#include "../include/server.h"

int to_parent(char *in_path)
{
    char *path = strdup(in_path);
    char *last = strrchr(path, '/');

    if (last == NULL) {
        free(path);
        return 0;
    }
    free(in_path);
    in_path = strndup(path, (int)(last - path));
    free(path);
    return 0;
}
