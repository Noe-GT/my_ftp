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
    int on = 1;

    if (sockfd < 0) {
        perror("socket creation failed");
        return -1;
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
        (char *)&on, sizeof(on)) < 0) {
            perror("setsockopt() failed");
            close(sockfd);
            return -1;
    }
    if (bind(sockfd, (struct sockaddr*)addr, addrlen) < 0) {
        perror("Bind failed");
        close(sockfd);
        return -1;
    }
    return sockfd;
}

struct pollfd *add_fd_to_array(struct pollfd *array, int new_fd, int a_size)
{
    struct pollfd *temp;
    int ti = 0;

    temp = (struct pollfd *)malloc(sizeof(struct pollfd) * (a_size + 1));
    for (int si = 0; si < a_size; si++) {
        temp[ti] = array[si];
        ti++;
    }
    temp[ti].fd = new_fd;
    temp[ti].events = POLLIN;
    free(array);
    return temp;
}

struct pollfd *remove_fd_from_array(struct pollfd *array, int elemi, int arr_s)
{
    struct pollfd *temp;
    int ti = 0;

    temp = (struct pollfd *)malloc(sizeof(struct pollfd) * arr_s - 1);
    for (int si = 0; si < arr_s; si++) {
        if (si == elemi)
            si++;
        if (si != arr_s) {
            temp[ti].fd = array[si].fd;
            temp[ti].events = array[si].events;
            ti++;
        }
    }
    free(array);
    return temp;
}
