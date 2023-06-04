/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** display_help.c
*/

#include "../include/my.h"

void display_help(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq\n");
    printf("\tport\tis the port number\n");
    printf("\twidth\tis the width of the world\n");
    printf("\theight\tis the height of the world\n");
    printf("\tnameX\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\tis the reciprocal of time unit for execution of actions\n");
}
