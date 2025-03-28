/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** modes
*/

#include "../include/server.h"

int close_pasv_socks(client_t *client)
{
    int out1 = 0;
    int out2 = 0;

    if (client->c_transfer_fd != -1) {
        out1 = close(client->c_transfer_fd);
        if (out1 < 0)
            perror("c_transfer_fd");
        client->c_transfer_fd = -1;
    }
    if (client->s_transfer_fd != -1) {
        out2 = close(client->s_transfer_fd);
        if (out2 < 0)
            perror("s_transfer_fd");
        client->s_transfer_fd = -1;
    }
    if (out1 < 0 || out2 < 0)
        return -1;
    return 0;
}

int connect_trans_sock(client_t *client)
{
    int new_fd = accept(client->s_transfer_fd, NULL, NULL);

    if (new_fd < 0) {
        if (errno != EWOULDBLOCK) {
            perror("ERROR: accept failed");
            send_buff(client->cmd_fd, "525 Accept failed.\r\n");
        }
        return -1;
    }
    client->c_transfer_fd = new_fd;
    return 0;
}

static int pasv_child(server_t *server, client_t *client, int out)
{
    server->stop_serv = true;
    if (connect_trans_sock(client) < 0) {
        perror("pasv_child");
        close_pasv_socks(client);
        return -1;
    }
    return out;
}

int passive_mode(server_t *server, client_t *client)
{
    int out = fork();

    if (out < 0) {
        perror("");
        send_buff(client->cmd_fd, "508 Fork failed.\r\n");
        return -1;
    } else if (out == 0)
        return pasv_child(server, client, out);
    else
        client->serv_status = PASSIVE;
    return out;
}
