/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** read_from_socket
*/

#include "../include/ftp.h"

static int check_cmd(server_t *server, char **tokens, int client_i)
{
    if (strcmp(tokens[0], "NOOP") == 0)
        return noop_cmd(server->client_fds[client_i].fd);
    if (strcmp(tokens[0], "QUIT") == 0)
        return quit_cmd(server, client_i);
    if (strcmp(tokens[0], "HELP") == 0)
        return help_cmd(server, client_i, tokens, my_array_len(tokens));
    send_buff(server->client_fds[client_i].fd, "Unknown command.\n");
    return 0;
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

int manage_client(server_t *server, int client_i)
{
    int client_fd = server->client_fds[client_i].fd;
    client_t *client = client_list_get_fd(server->clients, client_fd);
    char **tokens = tokenize(read_from_socket(client_fd));

    if (tokens == NULL)
        return -1;
    if (my_array_len(tokens) < 1) {
        printf("Client %d entered an invalid command\n", client_fd);
        free_array(tokens);
        return -1;
    }
    if (client->serv_status == NEEDUSER)
        return user_cmd(server, tokens);
    else if (client->serv_status == NEEDPASS)
        return pass_cmd(server, tokens);
    else
        return check_cmd(server, tokens, client_i);
}
