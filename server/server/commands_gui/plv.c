/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** plv.c
*/

#include "../../include/my.h"

void plv(this_t *this, player_t *player)
{
    if (this->cmd[1] == NULL || this->cmd[2] != NULL) {
        dprintf(player->socket, "ko\n");
        return;
    }
    list_players_t *tmp = this->players;
    for (; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->player->id, this->cmd[1]) == 0 && tmp->player->in_team == true) {
            dprintf(player->socket, "{\n\t\"id\": \"%s\",\n\t\"level\": %d\n}\n",
            tmp->player->id,
            tmp->player->level);
            return;
        }
    }
    dprintf(player->socket, "ko\n");
}