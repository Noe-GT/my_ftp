/*
** EPITECH PROJECT, 2025
** myLib
** File description:
** disp_files
*/

#include "my.h"

int disp_files(const char *path, int fd)
{
    DIR *dstream;
    struct dirent *dir;

    dstream = opendir(path);
    if (dstream) {
        dir = readdir(dstream);
        while (dir != NULL) {
            dprintf(fd, "%s\n", dir->d_name);
            dir = readdir(dstream);
        }
        closedir(dstream);
    }
    return 0;
}
