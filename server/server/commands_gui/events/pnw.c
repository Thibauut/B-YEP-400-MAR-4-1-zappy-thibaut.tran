/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** pnw.c
*/

#include "../../../include/my.h"

void pnw(this_t *this, player_t *player)
{
    list_players_t *tmp = this->players;
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->player->is_gui == true) {
            dprintf(tmp->player->socket, "{\n\t\"pnw_id\": \"%s\",\n\t\"pnw_x\": %d,\n\t\"pnw_y\": %d,\n\t\"pnw_o\": %d,\n\t\"pnw_level\": %d,\n\t\"pnw_team\": \"%s\"\n}\n",
            player->id,
            player->x,
            player->y,
            player->o,
            player->level,
            player->team->name);
        }
    }
}
