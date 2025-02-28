/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** commands
*/

#include "../../include/server.h"

int noop_cmd(int client_fd, int n_tokens)
{
    if (n_tokens != 1)
        return send_buff(client_fd, "511 wrong number of parameters.\n");
    if (send_buff(client_fd, "200\n") == -1)
        return -1;
    return 0;
}
