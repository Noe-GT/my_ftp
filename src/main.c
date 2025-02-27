/*
** EPITECH PROJECT, 2025
** ftp
** File description:
** main
*/

#include "../include/ftp.h"

// void test()
// {
//     char *client1 = (char *)malloc(sizeof(char) * 4);
//     char *client2 = (char *)malloc(sizeof(char) * 4);
//     char *client3 = (char *)malloc(sizeof(char) * 4);
//     linkedList *list = list_create(client1, 0);

//     list = list_add(list, 1, client2, 1);
//     list = list_add_end(list, client3, 2);
//     list_display(list);
//     list = list_remove(list, 1);
//     printf("\n");
//     list_display(list);
//     list = list_remove(list, 1);
//     printf("\n");
//     list_display(list);
//     list = list_remove(list, 0);
//     printf("\n");
//     list_display(list);
//     list_destroy(list);
// }

int main(int ac, char **av)
{
    server_t *server = (server_t *)malloc(sizeof(server_t));
    int out;

    if (ac != 3) {
        perror("Wrong number of arguments");
        return 84;
    }
    init(server, atoi(av[1]));
    out = run_server(server);
    free_all(server);
    if (out == -1)
        return 84;
    return 0;
}
