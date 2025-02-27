/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** commands
*/

#include "../../include/server.h"

int noop_cmd(int client_fd)
{
    if (send_buff(client_fd, "200") == -1)
        return -1;
    return 0;
}
