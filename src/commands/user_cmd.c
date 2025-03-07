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

static int pass_message(client_t *client, char *user)
{
    char *error_buff = malloc(sizeof(char) * (strlen(user) + 28));
    int out;

    sprintf(error_buff, "331 Password required for %s\n", user);
    out = send_buff(client->cmd_fd, error_buff);
    free(error_buff);
    return out;
}

int user_cmd(server_t *server, client_t *client, char **tokens, int n_tokens)
{
    user_t *user;

    if (n_tokens != 2)
        return error_parameters(client, "USER");
    if (client->serv_status != NEEDUSER)
        return error_notfound(client, "USER");
    user = check_user(server, tokens[1]);
    client->user = user;
    client->serv_status = NEEDPASS;
    if (pass_message(client, tokens[1]) < 0)
        return -1;
    return 0;
}
