/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** quit_cmd
*/

#include "../../include/server.h"

int quit_cmd(server_t *server, client_t *client)
{
    send_buff(client->fd, "221 Service closing control connection.\n");
    close(client->fd);
    printf("Client socket '%d' closed\n", client->fd);
    server->client_fds = remove_fd_from_array(server->client_fds,
        client->id, server->nfds);
    server->clients = client_list_remove_fd(server->clients, client->fd);
        server->nfds--;
    return 1;
}
