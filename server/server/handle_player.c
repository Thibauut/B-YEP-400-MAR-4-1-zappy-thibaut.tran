/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** handle_player.c
*/

#include "../include/my.h"

int add_player_to_team(this_t *this, player_t *player)
{
    list_teams_t *tmp = this->teams;
    for (; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->team->name, this->cmd[0]) == 0) {
            if (tmp->team->max_players - tmp->team->nb_players <= 0)
                return 1;
            tmp->team->nb_players += 1;
            player->team = tmp->team;
            // send game infos to player
            dprintf(player->socket, "%d\n", tmp->team->max_players - tmp->team->nb_players);
            dprintf(player->socket, "%d %d\n", this->width, this->height);
            return 0;
        }
    }
    return 1;
}
