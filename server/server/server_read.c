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
    list_players_t *tmp = this->players;
    if ((readValue = read(player->socket, buffer, 1024)) == 0) {
        if (player->is_gui == false && player->in_team == true) {
            delete_player(this, player);
            return;
        }
         if (player->is_gui == true && player->in_team == false) {
            FD_CLR(player->socket, &this->tmpfds);
            for (int i = 0; tmp; tmp = tmp->next) {
                if (tmp->player->is_gui == true && tmp->player->in_team == false
                && my_strcmp(tmp->player->id, player->id) == 0) {
                    close(player->socket);
                    player->socket = -1;
                    this->players = free_element_at(this->players, i);
                    break;
                }
            }
            return;
        }
        if (player->is_gui == false && player->in_team == false) {
            FD_CLR(player->socket, &this->tmpfds);
            for (int i = 0; tmp; tmp = tmp->next) {
                if (tmp->player->is_gui == false && tmp->player->in_team == false
                && my_strcmp(tmp->player->id, player->id) == 0) {
                    close(player->socket);
                    player->socket = -1;
                    this->players = free_element_at(this->players, i);
                    break;
                }
            }
            return;
        }
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
