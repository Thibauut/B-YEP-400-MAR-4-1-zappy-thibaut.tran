/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** pdr.c
*/

#include "../../../include/my.h"

void send_pdr_to_gui(this_t *this, char *drop_id, int resource)
{
    list_players_t *tmp_gui = this->players;
    for (; tmp_gui; tmp_gui = tmp_gui->next) {
        if (tmp_gui->player->is_gui == true) {
            pdr(this, tmp_gui->player, drop_id, resource);
            break;
        }
    }
}

void pdr(this_t *this, player_t *player, char *drop_id, int resource)
{
    dprintf(player->socket, "{\n\t\"pdr_id\": \"%s\",\n\t\"pdr_resource\": %d\n}\n", drop_id, resource);
}
