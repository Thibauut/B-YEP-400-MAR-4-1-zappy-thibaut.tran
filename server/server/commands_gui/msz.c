/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** msz.c
*/

#include "../../include/my.h"

void msz(this_t *this, player_t *player)
{
    dprintf(player->socket, "{\n\tx: %d,\n\ty: %d,\n}\n", this->width, this->height);
}