/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** server
*/

#include "../include/ftp.h"

int send_buff(int client_fd, char *buffer)
{
    int len = strlen(buffer);

    if (write(client_fd, buffer, len) < 0) {
        perror("ERROR : write failed");
        return -1;
    }
    return len;
}

int create_socket(struct sockaddr_in *addr, socklen_t addrlen)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int br;

    if (sockfd < 0) {
        perror("socket creation failed");
        return -1;
    }
    br = bind(sockfd, (struct sockaddr*)addr, addrlen);
    if (br < 0) {
        perror("Bind failed");
        return -1;
    }
    return sockfd;
}
