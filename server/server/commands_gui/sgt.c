/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** sgt.c
*/

#include "../../include/my.h"

void sgt(this_t *this, player_t *player)
{
    if (this->cmd[1] != NULL) {
        dprintf(player->socket, "ko\n");
        return;
    }
    dprintf(player->socket, "{\n\t\"sgt\": %d\n}\n", this->freq);
}
