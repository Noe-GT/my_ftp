/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** pass_cmd
*/

#include "../../include/server.h"

static int check_pass(client_t *client, char *password, int n_tokens)
{
    int is_pass;

    if (n_tokens == 1)
        is_pass = strcmp("", client->user->pass);
    else
        is_pass = strcmp(password, client->user->pass);
    if (is_pass != 0) {
        client->serv_status = NEEDUSER;
        return send_buff(client->cmd_fd, "530 Login incorrect.\r\n");
    }
    client->serv_status = NEUTRAL;
    if (send_buff(client->cmd_fd, "230 User logged in, proceed.\r\n") < 0)
        return -1;
    return 0;
}

int pass_cmd(client_t *client, char **tokens, int n_tokens)
{
    if (n_tokens > 2)
        return error_parameters(client, "PASS");
    if (client->serv_status != NEEDPASS)
        return send_buff(client->cmd_fd, "503 Login with USER first.\r\n");
    if (client->user == NULL) {
        client->serv_status = NEEDUSER;
        return send_buff(client->cmd_fd, "530 Login incorrect.\r\n");
    }
    return check_pass(client, tokens[1], n_tokens);
}
