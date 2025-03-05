/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** modes
*/

#include "../include/server.h"

void free_pasv(client_t *client)
{
    if (client->c_transfer_fd != -1)
        close(client->c_transfer_fd);
    if (client->s_transfer_fd != -1)
        close(client->s_transfer_fd);
}

int connect_trans_sock(client_t *client)
{
    int new_fd = accept(client->s_transfer_fd, NULL, NULL);

    if (new_fd < 0) {
        if (errno != EWOULDBLOCK) {
            perror("ERROR: accept failed");
            send_buff(client->cmd_fd, "525 Accept failed.\n");
        }
        return -1;
    }
    client->c_transfer_fd = new_fd;
    return 0;
}

static int pasv_child(server_t *server, client_t *client, int out)
{
    send_buff(client->cmd_fd, "I am child.\n");
    client->serv_status = PASSIVE_CHILD;
    server->stop_serv = true;
    if (connect_trans_sock(client) < 0) {
        free_pasv(client);
        return -1;
    }
    return out;
}

int passive_mode(server_t *server, client_t *client)
{
    int out = fork();

    if (out < 0) {
        perror("");
        send_buff(client->cmd_fd, "508 Fork failed.\n");
        return -1;
    } else if (out == 0) {
        pasv_child(server, client, out);
    } else {
        send_buff(client->cmd_fd, "I am parent.\n");
        client->serv_status = PASSIVE_PARENT;
        return out;
    }
}
