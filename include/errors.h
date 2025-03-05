/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** errors
*/

#ifndef ERRORS_H_
    #define ERRORS_H_
    #include "server.h"
    #include "client.h"

int error_notfound(client_t *client, char *cmd);
int error_parameters(client_t *client, char *cmd);
int error_login(client_t *client);

#endif /* !ERRORS_H_ */
