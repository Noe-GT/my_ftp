/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** main
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

int set_root_direct(server_t *server, char *path)
{
    if (directory_exists(path)) {
        server->root_directory = path;
        return 0;
    }
    perror(path);
    return -1;
}

int main(int ac, char **av)
{
    server_t *server = (server_t *)malloc(sizeof(server_t));
    int out;

    if (ac != 3) {
        perror("Wrong number of arguments.");
        free(server);
        return 84;
    }
    if (set_root_direct(server, av[2]) < 0) {
        free(server);
        return 84;
    }
    init(server, atoi(av[1]));
    out = run_server(server);
    free_all(server);
    if (out == -1)
        return 84;
    return 0;
}
