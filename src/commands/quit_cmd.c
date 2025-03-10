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
    close_pasv_socks(client);
    client_remove(server, client);
    printf("Client socket (%d) closed\n", temp);
    return 1;
}
