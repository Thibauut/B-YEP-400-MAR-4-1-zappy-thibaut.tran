/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** tna.c
*/

#include "../../include/my.h"

void tna(this_t *this, player_t *player)
{
    if (this->cmd[1] != NULL) {
        dprintf(player->socket, "ko\n");
        return;
    }
    dprintf(player->socket, "{\n\t\"teams\": [\n");
    list_teams_t *tmp = this->teams;
    for (; tmp != NULL; tmp = tmp->next) {
        dprintf(player->socket, "\t\t{\n\t\t\t\"name\": \"%s\"\n\t\t}", tmp->team->name);
        if (tmp->next != NULL)
            dprintf(player->socket, ",\n");
    }
    dprintf(player->socket, "\n\t]\n}\n");
}
