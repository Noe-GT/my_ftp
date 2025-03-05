/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** pwd_cmd
*/

#include "../../include/server.h"

static int change_direct(client_t *client, char *path)
{
    if (directory_exists(path)) {
        free(client->cwd);
        client->cwd = strdup(path);
    } else {
        return send_buff(client->cmd_fd,
            "501 Syntax error in parameters or arguments.\n");
    }
    return 0;
}

int cwd_cmd(client_t *client, char **tokens, int n_tokens)
{
    if (n_tokens != 2)
        return error_parameters(client, "CWD");
    if (client->serv_status != TEST &&
        (client->serv_status == NEEDUSER || client->serv_status == NEEDPASS))
        return error_login(client);
    if (change_direct(client, tokens[1]) < 0)
        return -1;
    if (send_buff(client->cmd_fd,
        "250 Requested file action okay, completed.\n") < 0)
        return -1;
    return 0;
}
