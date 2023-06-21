/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** pex.c
*/

#include "../../../include/my.h"

void send_pex_to_gui(this_t *this, char *uuid)
{
    list_players_t *tmp_gui = this->players;
    for (; tmp_gui; tmp_gui = tmp_gui->next) {
        if (tmp_gui->player->is_gui == true) {
            pex(this, tmp_gui->player, uuid);
            break;
        }
    }
}

void pex(this_t *this, player_t *player, char *player_id)
{
    dprintf(player->socket, "{\n\t\"cmd\": \"pex\",\n\t\"id\": \"%s\"\n}\n", player_id);
}