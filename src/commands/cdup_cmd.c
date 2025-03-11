/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** cdup_cmd
*/

/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** pwd_cmd
*/

#include "../../include/server.h"

static int change_direct(client_t *client)
{
    char *path = strdup(client->cwd);
    char *last = strrchr(path, '/');

    if (last == NULL) {
        free(path);
        return 0;
    }
    free(client->cwd);
    client->cwd = strndup(path, (int)(last - path));
    free(path);
    return 0;
}

int cdup_cmd(client_t *client, int n_tokens)
{
    if (n_tokens != 1)
        return error_parameters(client, "CDUP");
    if (client->serv_status != TEST &&
        (client->serv_status == NEEDUSER || client->serv_status == NEEDPASS))
        return error_login(client);
    if (change_direct(client) < 0)
        return -1;
    if (send_buff(client->cmd_fd,
        "250 Requested file action okay, completed.\r\n") < 0)
        return -1;
    return 0;
}
