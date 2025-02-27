/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** quit_cmd
*/

#include "../../include/server.h"

int quit_cmd(server_t *server, int client_i)
{
    int client_fd = server->client_fds[client_i].fd;

    send_buff(client_fd, "221 Service closing control connection.\n");
    close(client_fd);
    printf("Client socket '%d' closed\n", client_fd);
    server->clients = client_list_remove_fd(server->clients, client_fd);
    server->client_fds = remove_fd_from_array(server->client_fds,
        client_i, server->nfds);
    server->nfds--;
    return 1;
}
