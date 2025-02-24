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
    int res = 0;

    if (ac != 2) {
        perror("Wrong number of arguments");
        return 1;
    }
    init(server, atoi(av[1]));
    res = run_server(server);
    free_all(server);
    return res;
}
