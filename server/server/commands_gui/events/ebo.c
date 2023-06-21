/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** ebo.c
*/

#include "../../../include/my.h"

void send_ebo_to_gui(this_t *this, char *uuid)
{
    list_players_t *tmp_gui = this->players;
    for (; tmp_gui; tmp_gui = tmp_gui->next) {
        if (tmp_gui->player->is_gui == true) {
            ebo(this, tmp_gui->player, uuid);
            break;
        }
    }
}

void ebo(this_t *this, player_t *player, char *uuid)
{
    dprintf(player->socket, "{\n\t\"cmd\": \"ebo\",\n\t\"id\": \"%s\"\n}\n", uuid);
}
