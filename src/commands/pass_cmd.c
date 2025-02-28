/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** pass_cmd
*/

#include "../../include/server.h"

int pass_cmd(client_t *client, char **tokens, int n_tokens)
{
    int is_pass;

    if (n_tokens > 2)
        return send_buff(client->fd, "511 wrong number of parameters.\n");
    if (client->serv_status == NEEDUSER)
        return send_buff(client->fd, "332 Need account for login.\n");
    if (client->serv_status != NEEDPASS)
        return send_buff(client->fd, "506 command not available.\n");
    if (n_tokens == 1)
        is_pass = strcmp("", client->user->pass);
    else
        is_pass = strcmp(tokens[1], client->user->pass);
    if (is_pass != 0)
        return send_buff(client->fd, "513 Invalid password.\n");
    client->serv_status = NEUTRAL;
    if (send_buff(client->fd, "230 User logged in, proceed.\n") < 0)
        return -1;
    return 0;
}
