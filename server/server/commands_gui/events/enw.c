/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** enw.c
*/

#include "../../../include/my.h"

void send_enw_to_gui(this_t *this, player_t *player, egg_t *egg)
{
    list_players_t *tmp_gui = this->players;
    for (; tmp_gui; tmp_gui = tmp_gui->next) {
        if (tmp_gui->player->is_gui == true) {
            enw(this, tmp_gui->player, egg);
            break;
        }
    }
}

void enw(this_t *this, player_t *player, egg_t *egg)
{
    dprintf(player->socket, "{\n\t\"cmd\": \"enw\",\n\t\"egg_id\": \"%s\",\n\t\"player_id\": \"%s\",\n\t\"x\": %d,\n\t\"y\": %d\n}\n", egg->id, egg->uuid_creator, egg->x, egg->y);
}
