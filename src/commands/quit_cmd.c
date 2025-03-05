/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** quit_cmd
*/

#include "../../include/server.h"

int quit_cmd(server_t *server, client_t *client, int n_tokens)
{
    send_buff(client->cmd_fd, "221 Goodbye.\n");
    if (close(client->cmd_fd) < 0) {
        fprintf(stderr, "%d: %s\n", client->cmd_fd, errno);
        return -1;
    }
    printf("Client socket '%d' closed\n", client->cmd_fd);
    server->client_fds = remove_fd_from_array(server->client_fds,
        client->id, server->nfds);
    server->clients = client_list_remove_fd(server->clients, client->cmd_fd);
        server->nfds--;
    return 1;
}
