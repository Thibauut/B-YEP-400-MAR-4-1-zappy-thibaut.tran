/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** msz.c
*/

#include "../../include/my.h"

void msz(this_t *this, player_t *player)
{
    if (this->cmd[1] != NULL) {
        dprintf(player->socket, "ko\n");
        return;
    }
    dprintf(player->socket, "{\n\t\"cmd\": \"msz\",\n\t\"x\": %d,\n\t\"y\": %d\n}\n", this->width, this->height);
}
