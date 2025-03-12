/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** stor_cmd
*/

#include "../../include/server.h"

static int check_error(client_t *client, int n_tokens)
{
    if (n_tokens != 2)
        return error_parameters(client, "stor");
    if (client->serv_status != TEST &&
        (client->serv_status == NEEDUSER || client->serv_status == NEEDPASS))
        return error_login(client);
    if (client->serv_status != PASSIVE &&
        client->serv_status != ACTIVE)
        return send_buff(client->cmd_fd, "506 command not available.\r\n");
    return 1;
}

static void read_and_write(int r_fd, int w_fd)
{
    size_t len = 0;
    char *buff = (char *)malloc(sizeof(char) * len);
    char *t_buff = (char *)malloc(sizeof(char) * 1);
    int r_out = read(r_fd, t_buff, 1);

    while (r_out != 0 && t_buff[0] != '\n') {
        len++;
        buff = realloc(buff, len);
        strcat(buff, t_buff);
        r_out = read(r_fd, t_buff, 1);
    }
    if (write(w_fd, buff, len) < 0)
        perror("read_and_write");
    free(t_buff);
    free(buff);
    close(w_fd);
}

static void stor_child(server_t *server, client_t *client, int f_fd)
{
    read_and_write(client->c_transfer_fd, f_fd);
    send_buff(client->cmd_fd, "226 File sent, closing socket\r\n");
    free_passive(server);
    exit(0);
}

int stor_cmd(server_t *server, client_t *client, char **tokens, int n_tokens)
{
    int fout;
    char *path;
    int f_fd;

    if (check_error(client, n_tokens) != 1)
        return -1;
    path = concat_paths(client->cwd, tokens[1]);
    f_fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (f_fd < 0) {
        send_buff(client->cmd_fd, "550 can't create file\r\n");
        return -1;
    }
    send_buff(client->cmd_fd, "150 opening data socket\r\n");
    fout = passive_mode(server, client);
    if (fout != 0) {
        client->serv_status = NEUTRAL;
        return fout;
    }
    stor_child(server, client, f_fd);
    return 0;
}
