/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** pbc.c
*/

#include "../../../include/my.h"

void send_pbc_to_gui(this_t *this, char *uuid, char *msg)
{
    list_players_t *tmp_gui = this->players;
    for (; tmp_gui; tmp_gui = tmp_gui->next) {
        if (tmp_gui->player->is_gui == true) {
            pbc(this, tmp_gui->player, uuid, msg);
            break;
        }
    }
}

void pbc(this_t *this, player_t *player, char *uuid, char *msg)
{
    dprintf(player->socket, "{\n\t\"cmd\": \"pbc\",\n\t\"id\": \"%s\",\n\t\"msg\": \"%s\"\n}\n", uuid, msg);
}
