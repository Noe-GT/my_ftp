/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** user_cmd
*/

#include "../../include/server.h"

user_t *check_user(server_t *server, char *user_name)
{
    for (int i = 0; i < server->n_users; i++) {
        if (strcmp(server->users[i]->name, user_name) == 0)
            return server->users[i];
    }
    return NULL;
}

int user_cmd(server_t *server, client_t *client, char **tokens, int n_tokens)
{
    user_t *user;

    if (n_tokens != 2)
        return send_buff(client->fd, "511 wrong number of parameters.\n");
    if (client->serv_status != NEEDUSER)
        return send_buff(client->fd, "506 command not available.\n");
    user = check_user(server, tokens[1]);
    if (user == NULL)
        return send_buff(client->fd, "512 Invalid username.\n");
    client->user = user;
    client->serv_status = NEEDPASS;
    if (send_buff(client->fd, "331 User name okay, need password.\n") < 0)
        return -1;
    return 0;
}
