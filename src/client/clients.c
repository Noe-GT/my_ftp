/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** client
*/

#include "../../include/server.h"

int client_remove(server_t *server, client_t *client)
{
    server->client_fds = remove_fd_from_array(server->client_fds,
        client->id, server->nfds);
    if (client->cmd_fd == -1)
        return 0;
    if (shutdown(client->cmd_fd, SHUT_RDWR) < 0) {
        perror("QUIT");
        return -1;
    }
    server->clients = client_list_remove_fd(server->clients, client->cmd_fd);
    server->nfds--;
    return 0;
}
