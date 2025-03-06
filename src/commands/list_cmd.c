/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** list_cmd
*/

#include "../../include/server.h"

int list_cmd(server_t *server, client_t *client, char **tokens, int n_tokens)
{
    int fout;

    (void)server;
    printf("tok : %s / n : %d\n", tokens[1], n_tokens);
    send_buff(client->cmd_fd, "000 test list.\n");
    fout = passive_mode(server, client);
    if (fout != 0)
        return fout;
    send_buff(client->cmd_fd, "000 test\n");
    free_passive(server);
    exit(0);
}
