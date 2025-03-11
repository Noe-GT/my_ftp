/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** errors
*/

#include "../include/errors.h"

int error_notfound(client_t *client, char *cmd)
{
    char *error_buff = malloc(sizeof(char) * (strlen(cmd) + 22));
    int out;

    sprintf(error_buff, "500 %s not understood\r\n", cmd);
    out = send_buff(client->cmd_fd, error_buff);
    free(error_buff);
    return out;
}

int error_login(client_t *client)
{
    return send_buff(client->cmd_fd,
        "530 Please login with USER and PASS\r\n");
}

int error_parameters(client_t *client, char *cmd)
{
    char *error_buff = malloc(sizeof(char) * (strlen(cmd) + 37));
    int out;

    sprintf(error_buff, "500 %s: command requires a parameter\r\n", cmd);
    out = send_buff(client->cmd_fd, error_buff);
    free(error_buff);
    return out;
}
