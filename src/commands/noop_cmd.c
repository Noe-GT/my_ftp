/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** commands
*/

#include "../../include/server.h"

int noop_cmd(int client_fd, int n_tokens)
{
    if (send_buff(client_fd, "200 NOOP command successful\n") == -1)
        return -1;
    return 0;
}
