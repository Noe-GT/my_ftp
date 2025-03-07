/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** shared
*/

#ifndef SHARED_H_
    #define SHARED_H_
    #include "include.h"

typedef enum serv_status_e {
    NONE,
    NEEDUSER,
    NEEDPASS,
    NEUTRAL,
    PASSIVE_CHILD,
    PASSIVE_PARENT,
    ACTIVE,
    TEST
} serv_status_t;

typedef struct user_s {
    char *name;
    char *pass;
} user_t;

#endif /* !SHARED_H_ */
