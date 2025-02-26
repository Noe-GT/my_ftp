/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** main
*/

#include "../include/ftp.h"

int main(int ac, char **av)
{
    server_t *server = (server_t *)malloc(sizeof(server_t));
    int out;

    if (ac != 3) {
        perror("Wrong number of arguments");
        return 84;
    }
    init(server, atoi(av[1]));
    out = run_server(server);
    free_all(server);
    if (out == -1)
        return 84;
    return 0;
}
