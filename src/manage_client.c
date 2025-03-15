/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** read_from_socket
*/

#include "../include/ftp.h"

static int check_file_cmds(server_t *server, client_t *client,
    char **tokens, int n_tokens)
{
    if (strcmp(tokens[0], "LIST") == 0)
        return list_cmd(server, client, tokens, n_tokens);
    if (strcmp(tokens[0], "RETR") == 0)
        return retr_cmd(server, client, tokens, n_tokens);
    if (strcmp(tokens[0], "STOR") == 0)
        return stor_cmd(server, client, tokens, n_tokens);
    if (strcmp(tokens[0], "DELE") == 0)
        return dele_cmd(client, tokens, n_tokens);
    return error_notfound(client, tokens[0]);
}

static int check_cmds(server_t *server, client_t *client,
    char **tokens, int n_tokens)
{
    if (strcmp(tokens[0], "QUIT") == 0)
        return quit_cmd(server, client);
    if (strcmp(tokens[0], "NOOP") == 0)
        return noop_cmd(client->cmd_fd);
    if (strcmp(tokens[0], "HELP") == 0)
        return help_cmd(server, client, tokens, n_tokens);
    if (strcmp(tokens[0], "USER") == 0)
        return user_cmd(server, client, tokens, n_tokens);
    if (strcmp(tokens[0], "PASS") == 0)
        return pass_cmd(client, tokens, n_tokens);
    if (strcmp(tokens[0], "PWD") == 0)
        return pwd_cmd(client, n_tokens);
    if (strcmp(tokens[0], "CWD") == 0)
        return cwd_cmd(client, tokens, n_tokens);
    if (strcmp(tokens[0], "CDUP") == 0)
        return cdup_cmd(client, n_tokens);
    if (strcmp(tokens[0], "PASV") == 0)
        return pasv_cmd(client, n_tokens);
    return check_file_cmds(server, client, tokens, n_tokens);
}

static char **tokenize(char *buffer)
{
    char **tokens;

    if (buffer == NULL)
        return NULL;
    tokens = str_to_array(buffer, " ");
    free(buffer);
    return tokens;
}

static char *handle_buff(char *t_buff, char *res_buff, int len)
{
    if (len == 2)
        strcpy(res_buff, t_buff);
    else
        strcat(res_buff, t_buff);
    return res_buff;
}

static char *read_from_socket(int r_fd)
{
    size_t len = 1;
    char *res_buff = (char *)malloc(sizeof(char) * len);
    char *t_buff = (char *)malloc(sizeof(char) * 2);
    int r_out = read(r_fd, t_buff, 1);

    t_buff[1] = '\0';
    while (r_out != 0 && t_buff[0] != '\n') {
        if (t_buff[0] != '\r') {
            len++;
            res_buff = realloc(res_buff, len);
            res_buff = handle_buff(t_buff, res_buff, len);
        }
        r_out = read(r_fd, t_buff, 1);
        t_buff[1] = '\0';
    }
    free(t_buff);
    res_buff[len - 1] = '\0';
    return res_buff;
}

int manage_commands(server_t *server, client_t *client)
{
    char *cmd_buff = read_from_socket(client->cmd_fd);
    int n_tokens = 0;
    int out = -1;
    char **tokens;

    if (strlen(cmd_buff) < 1 || cmd_buff[0] == ' ') {
        free(cmd_buff);
        return -1;
    }
    tokens = tokenize(cmd_buff);
    if (tokens == NULL)
        return -1;
    n_tokens = my_array_len(tokens);
    if (n_tokens >= 1)
        out = check_cmds(server, client, tokens, n_tokens);
    free_array(tokens);
    return out;
}

int manage_client(server_t *server, int client_i)
{
    int client_fd = server->client_fds[client_i].fd;
    client_t *client = client_list_get_fd(server->clients, client_fd);

    client->id = client_i;
    return manage_commands(server, client);
}
