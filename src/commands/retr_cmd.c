/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** retr_cmd
*/

#include "../../include/server.h"

static int check_error(client_t *client, int n_tokens)
{
    if (n_tokens != 2)
        return error_parameters(client, "RETR");
    if (client->serv_status != TEST &&
        (client->serv_status == NEEDUSER || client->serv_status == NEEDPASS))
        return error_login(client);
    if (client->serv_status != PASSIVE &&
        client->serv_status != ACTIVE)
        return send_buff(client->cmd_fd, "425 command not available.\r\n");
    return 1;
}

static int print_file(char *path, int p_fd)
{
    struct stat st;
    size_t size;
    char *buff;
    int f_fd;

    stat(path, &st);
    size = st.st_size;
    buff = (char *)malloc(sizeof(char) * size);
    f_fd = open(path, O_RDONLY);
    read(f_fd, buff, size);
    send_buff(p_fd, buff);
    free(buff);
    return 0;
}

static void retr_child(server_t *server, client_t *client, char *path)
{
    send_buff(client->cmd_fd, "226 File sent, closing socket\r\n");
    print_file(path, client->c_transfer_fd);
    send_buff(client->c_transfer_fd, "\r\n");
    free_passive(server);
    exit(0);
}

int retr_cmd(server_t *server, client_t *client, char **tokens, int n_tokens)
{
    int fout;
    char *path;

    if (check_error(client, n_tokens) != 1)
        return -1;
    path = concat_paths(client->cwd, tokens[1]);
    if (access(path, R_OK) != 0) {
        send_buff(client->cmd_fd, "550 can't access file\r\n");
        return -1;
    }
    send_buff(client->cmd_fd, "150 opening data socket\r\n");
    fout = passive_mode(server, client);
    if (fout != 0) {
        client->serv_status = NEUTRAL;
        return fout;
    }
    retr_child(server, client, path);
    return 0;
}
