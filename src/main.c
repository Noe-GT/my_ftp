/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** main
*/

#include "../include/ftp.h"

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
    int out = -1;

    if (ac != 3) {
        perror("Wrong number of arguments.");
        free(server);
        return 84;
    }
    if (set_root_direct(server, av[2]) < 0) {
        free(server);
        return 84;
    }
    if (init(server, atoi(av[1])) == 0)
        out = run_server(server);
    free_all(server);
    if (out == -1)
        return 84;
    return 0;
}
