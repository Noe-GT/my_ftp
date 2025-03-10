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

char **tokenize(char *buffer)
{
    char *clean;
    char **tokens;

    if (buffer == NULL)
        return NULL;
    clean = clean_str(buffer, "\n\r");
    tokens = my_str_to_word_array(clean, " ");
    free(clean);
    free(buffer);
    return tokens;
}

char *read_from_socket(int client_fd)
{
    char *buffer = (char *)malloc(sizeof(char) * 1000);
    int len = read(client_fd, buffer, 1000 - 1);

    if (len == -1) {
        printf("ERROR: read failed for client %d\n", client_fd);
        return NULL;
    }
    buffer[len] = '\0';
    return buffer;
}

int manage_commands(server_t *server, client_t *client)
{
    char **tokens = tokenize(read_from_socket(client->cmd_fd));
    int n_tokens = 0;

    if (tokens == NULL)
        return -1;
    n_tokens = my_array_len(tokens);
    if (n_tokens < 1) {
        printf("Client %d entered an invalid command\n", client->cmd_fd);
        free_array(tokens);
        return -1;
    }
    return check_cmds(server, client, tokens, n_tokens);
}

int manage_client(server_t *server, int client_i)
{
    int client_fd = server->client_fds[client_i].fd;
    client_t *client = client_list_get_fd(server->clients, client_fd);

    client->id = client_i;
    return manage_commands(server, client);
}
