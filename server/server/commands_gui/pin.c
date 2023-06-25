/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** pin.c
*/

#include "../../include/my.h"

void pin(this_t *this, player_t *player)
{
    if (this->cmd[1] == NULL || this->cmd[2] != NULL) {
        dprintf(player->socket, "ko\n");
        return;
    }
    list_players_t *tmp = this->players;
    for (; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->player->id, this->cmd[1]) == 0 && tmp->player->in_team == true) {
            dprintf(player->socket, "{\n\t\"cmd\": \"pin\",\n\t\"id\": \"%s\",\n\t\"x\": %d,\n\t\"y\": %d,\n\t\"food\": %d,\n\t\"linemate\": %d,\n\t\"deraumere\": %d,\n\t\"sibur\": %d,\n\t\"mendiane\": %d,\n\t\"phiras\": %d,\n\t\"thystame\": %d\n}\n",
            tmp->player->id,
            tmp->player->x,
            tmp->player->y,
            tmp->player->inventory->food,
            tmp->player->inventory->linemate,
            tmp->player->inventory->deraumere,
            tmp->player->inventory->sibur,
            tmp->player->inventory->mendiane,
            tmp->player->inventory->phiras,
            tmp->player->inventory->thystame);
            return;
        }
    }
    dprintf(player->socket, "ko\n");
}