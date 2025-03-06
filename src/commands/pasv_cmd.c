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

static int pasv_message(client_t *client)
{
    char ip[16];
    unsigned int port;
    struct sockaddr_in addr;
    socklen_t len;
    char *ip_parse;

    bzero(&addr, sizeof(addr));
    len = sizeof(addr);
    getsockname(client->s_transfer_fd, (struct sockaddr *) &addr, &len);
    inet_ntop(AF_INET, &addr.sin_addr, ip, sizeof(ip));
    port = ntohs(addr.sin_port);
    ip_parse = strtok(ip, ".");
    if (dprintf(client->cmd_fd,
        "227 Entering Passive Mode (%s,%s,%s,%s,%d,%d).\n",
        ip_parse, ip_parse, ip_parse, ip_parse, port / 256, port % 256) < 0)
        return -1;
    return 0;
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
        perror("pasv");
        return -1;
    }
    client->serv_status = PASSIVE_PARENT;
    return pasv_message(client);
}
