/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** read_server.c
*/

#include "../include/my.h"

void read_data(this_t *this, player_t *player, int i)
{
    int readValue = 0;
    char buffer[1024] = "\0";
    if ((readValue = read(player->socket, buffer, 1024)) == 0) {
        close(player->socket);
        FD_CLR(player->socket, &this->tmpfds);
        player->socket = 0;
    } else {
        this->cmd = NULL;
        char *tmp = strdup(buffer);
        this->cmd = strtok_wordtab(tmp, "  \t\n\r");
        commands(this, player);
    }
}

void data_from_player(this_t *this)
{
    list_players_t *tmp = this->players;
    for (int i = 0; tmp != NULL; i++, tmp = tmp->next) {
        if (FD_ISSET(tmp->player->socket, &this->tmpfds))
            read_data(this, tmp->player, i);
    }
}
