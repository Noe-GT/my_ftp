/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** pasv_cmd
*/

#include "../../include/server.h"

static int set_passive(client_t *client)
{
    struct sockaddr_in *addr = make_addr(0);

    client->s_transfer_fd = create_socket(addr, sizeof(*addr), 2);
    return client->s_transfer_fd;
}

int pasv_cmd(client_t *client, int n_tokens)
{
    if (n_tokens != 1)
        return error_parameters(client, "PASV");
    if (client->serv_status != TEST &&
        (client->serv_status == NEEDUSER || client->serv_status == NEEDPASS))
        return error_login(client);
    if (client->serv_status != NEUTRAL &&
        client->serv_status != ACTIVE &&
        client->serv_status != TEST)
        return send_buff(client->cmd_fd, "506 command not available.\n");
    if (set_passive(client) < 0) {
        perror("quit");
        return -1;
    }
    client->serv_status = PASSIVE_PARENT;
    if (send_buff(client->cmd_fd,
        "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\n") < 0)
        return -1;
    return 0;
}
