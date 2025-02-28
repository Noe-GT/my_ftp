/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** pwd_cmd
*/

#include "../../include/server.h"

int pwd_cmd(client_t *client, int n_tokens)
{
    char print_buff[500];

    if (n_tokens != 1)
        return send_buff(client->fd, "511 wrong number of parameters.\n");
    if (client->serv_status != TEST && client->serv_status == NEEDUSER)
        return send_buff(client->fd, "332 Need account for login.\n");
    if (client->serv_status != PASSIVE &&
        client->serv_status != ACTIVE &&
        client->serv_status != TEST)
        return send_buff(client->fd, "506 command not available.\n");
    sprintf(print_buff, "257 %s created\n", client->cwd);
    if (send_buff(client->fd, print_buff) < 0)
        return -1;
    return 0;
}
