/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** connect_nbr.c
*/

#include "../../include/my.h"

void connect_nbr(this_t *this, player_t *player)
{
    dprintf(player->socket, "%d\n", this->nb_clients - player->team->nb_players);
}
