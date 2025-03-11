/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** pwd_cmd
*/

#include "../../include/server.h"

static int change_direct(client_t *client, char *path)
{
    char *new_path = concat_paths(client->cwd, path);

    if (directory_exists(new_path)) {
        free(client->cwd);
        client->cwd = strdup(new_path);
    } else {
        free(new_path);
        send_buff(client->cmd_fd,
            "501 Incorrect path.\r\n");
        return -1;
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
    if (dprintf(client->cmd_fd, "250 wd updated to '%s'\n", client->cwd) < 0)
        return -1;
    return 0;
}
