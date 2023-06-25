/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** pfk.c
*/

#include "../../../include/my.h"

void send_pfk_to_gui(this_t *this, char *uuid)
{
    list_players_t *tmp_gui = this->players;
    for (; tmp_gui; tmp_gui = tmp_gui->next) {
        if (tmp_gui->player->is_gui == true) {
            pfk(this, tmp_gui->player, uuid);
            break;
        }
    }
}

void pfk(this_t *this, player_t *player, char *uuid)
{

    dprintf(player->socket, "{\n\t\"cmd\": \"pfk\",\n\t\"id\": \"%s\"\n}\n", uuid);
}