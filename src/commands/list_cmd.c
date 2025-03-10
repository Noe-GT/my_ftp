/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** list_cmd
*/

#include "../../include/server.h"

static int check_error(client_t *client, int n_tokens)
{
    if (n_tokens > 2)
        return error_parameters(client, "LIST");
    if (client->serv_status != TEST &&
        (client->serv_status == NEEDUSER || client->serv_status == NEEDPASS))
        return error_login(client);
    if (client->serv_status != PASSIVE &&
        client->serv_status != ACTIVE)
        return send_buff(client->cmd_fd, "506 command not available.\n");
    return 1;
}

static void list_child(server_t *server, client_t *client, char *path)
{
    send_buff(client->cmd_fd, "226 List sent, closing socket\n");
    dup2(client->c_transfer_fd, 1);
    execlp("ls", "ls", "-l", path, NULL);
    free_passive(server);
    exit(0);
}

int list_cmd(server_t *server, client_t *client, char **tokens, int n_tokens)
{
    int fout;
    char *path = client->cwd;

    if (check_error(client, n_tokens) != 1)
        return -1;
    if (n_tokens == 2)
        path = tokens[1];
    if (!is_directory(path)) {
        send_buff(client->cmd_fd, "550 Invalid path\n");
        return -1;
    }
    send_buff(client->cmd_fd, "150 opening data socket\n");
    fout = passive_mode(server, client);
    if (fout != 0) {
        client->serv_status = NEUTRAL;
        return fout;
    }
    list_child(server, client, path);
    return 0;
}
