/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** quit_cmd
*/

#include "../../include/server.h"

int quit_cmd(server_t *server, client_t *client)
{
    int temp = (int)client->cmd_fd;

    send_buff(client->cmd_fd, "221 Goodbye.\n");
    free_pasv(client);
    server->client_fds = remove_fd_from_array(server->client_fds,
        client->id, server->nfds);
    if (shutdown(client->cmd_fd, SHUT_RDWR) < 0) {
        perror("QUIT");
        return -1;
    }
    server->clients = client_list_remove_fd(server->clients, client->cmd_fd);
    server->nfds--;
    printf("Client socket (%d) closed\n", temp);
    return 1;
}
