/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** help_cmd
*/

#include "../../include/server.h"

static int send_help(server_t *server, int client_fd)
{
    char buff[200];

    for (int i = 0; server->available_cmds[i] != NULL; i++) {
        sprintf(buff, "%s\n", server->cmds_desc[i]);
        if (send_buff(client_fd, buff) < 0)
            return -1;
    }
    return 0;
}

static int send_help_cmd(server_t *server, int client_fd, char *cmd)
{
    char buff[200];

    for (int i = 0; server->available_cmds[i] != NULL; i++) {
        if (strcmp(server->available_cmds[i], cmd) == 0) {
            sprintf(buff, "%s\n", server->cmds_desc[i]);
            return send_buff(client_fd, buff);
        }
    }
    return 0;
}

int help_cmd(server_t *server, client_t *client, char **tokens, int n_tokens)
{
    int res = 0;

    if (n_tokens != 1)
        return error_parameters(client, "HELP");
    if (send_buff(client->cmd_fd,
        "214-The following commands are recognized:\n") < 0)
        return -1;
    if (n_tokens == 2)
        res = send_help_cmd(server, client->cmd_fd, tokens[1]);
    if (res == -1)
        return -1;
    if (res > 1)
        return 0;
    return send_help(server, client->cmd_fd);
}
