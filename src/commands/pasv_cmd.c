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

static int pasv_print(client_t *client, char *ip, int port)
{
    char *ip_parse = strtok(ip, ".");

    if (dprintf(client->cmd_fd, "227 Entering Passive Mode (") < 0)
        return -1;
    while (ip_parse != NULL) {
        if (dprintf(client->cmd_fd, "%s,", ip_parse) < 0)
            return -1;
        ip_parse = strtok(NULL, ".");
    }
    if (dprintf(client->cmd_fd, "%d,%d).\r\n", port / 256, port % 256) < 0)
        return -1;
    return 0;
}

static int pasv_message(client_t *client)
{
    char ip[16];
    unsigned int port;
    struct sockaddr_in addr;
    struct sockaddr_in caddr = *client->transfer_addr;
    socklen_t len;

    bzero(&addr, sizeof(addr));
    len = sizeof(addr);
    getsockname(client->s_transfer_fd, (struct sockaddr *) &addr, &len);
    port = ntohs(addr.sin_port);
    inet_ntop(AF_INET, &caddr.sin_addr, ip, sizeof(ip));
    return pasv_print(client, ip, port);
}

int pasv_cmd(client_t *client, int n_tokens)
{
    if (n_tokens != 1)
        return error_parameters(client, "PASV");
    if (client->serv_status != TEST &&
        (client->serv_status == NEEDUSER || client->serv_status == NEEDPASS))
        return error_login(client);
    if (client->serv_status != NEUTRAL &&
        client->serv_status != PASSIVE &&
        client->serv_status != TEST)
        return send_buff(client->cmd_fd, "506 command not available.\r\n");
    if (client->serv_status != PASSIVE) {
        if (set_passive(client) < 0) {
            perror("pasv");
            return -1;
        }
    }
    client->serv_status = PASSIVE;
    return pasv_message(client);
}
