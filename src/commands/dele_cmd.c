/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** dele_cmd
*/

#include "../../include/server.h"

int del_file(client_t *client, char *filename)
{
    int len = strlen(client->cwd) + strlen(filename) + 1;
    char *path = (char *)malloc(sizeof(char) * len);

    strcpy(path, client->cwd);
    strcat(path, "/");
    strcat(path, filename);
    if (remove(path) == 0)
        return send_buff(client->cmd_fd,
            "250 Requested file action okay, completed.\n");
    if (errno == EBUSY)
        return send_buff(client->cmd_fd,
            "450 Requested file action not taken. File unavailable.\n");
    return send_buff(client->cmd_fd,
        "550 Requested action not taken. File unavailable.\n");
}

int dele_cmd(client_t *client, char **tokens, int n_tokens)
{
    if (n_tokens != 2)
        return error_parameters(client, "DELE");
    if (client->serv_status != TEST &&
        (client->serv_status == NEEDUSER || client->serv_status == NEEDPASS))
        return error_login(client);
    return del_file(client, tokens[1]);
}
