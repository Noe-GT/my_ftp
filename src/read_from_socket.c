/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** read_from_socket
*/

#include "../include/ftp.h"

static int check_cmd(server_t *server, char *buffer, int client_fd)
{
    char *clean = clean_str(buffer, "\n\r");
    char **tokens = my_str_to_word_array(clean, " ");
    int len = my_array_len(tokens);

    if (len == 1 && strcmp(tokens[0], "QUIT") == 0)
        return quit_cmd(server, client_fd);
    if ((len == 1 || len == 2) && strcmp(tokens[0], "HELP") == 0)
        return help_cmd(server, client_fd, tokens, len);
    return 0;
}

int read_from_socket(server_t *server, int client_fd)
{
    char buffer[1000];
    int len = read(client_fd, buffer, 1000 - 1);

    buffer[len] = '\0';
    return check_cmd(server, buffer, client_fd);
}
