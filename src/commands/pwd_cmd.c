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
        return error_parameters(client, "PWD");
    if (client->serv_status != TEST &&
        (client->serv_status == NEEDUSER ||
        client->serv_status == NEEDPASS))
        return error_login(client);
    sprintf(print_buff, "257 %s\r\n", client->cwd);
    if (send_buff(client->cmd_fd, print_buff) < 0)
        return -1;
    return 0;
}
