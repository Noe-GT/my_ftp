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

char *concat_paths(char *path1, char *path2)
{
    int len = strlen(path1) + strlen(path2) + 2;
    char *new_path = (char *)malloc(sizeof(char) * len);

    strcpy(new_path, path1);
    strcat(new_path, "/");
    strcat(new_path, path2);
    return new_path;
}
