/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** pie.c
*/

#include "../../../include/my.h"

void send_pie_to_gui(this_t *this, int x, int y, char *r)
{
    list_players_t *tmp_gui = this->players;
    for (; tmp_gui; tmp_gui = tmp_gui->next) {
        if (tmp_gui->player->is_gui == true) {
            pie(this, tmp_gui->player, x, y, r);
            break;
        }
    }
}

void pie(this_t *this, player_t *player, int x, int y, char *r)
{
    dprintf(player->socket, "{\n\t\"cmd\": \"pie\",\n\t\"x\": %d,\n\t\"y\": %d\n\t\"r\": \"%s\"\n}\n", x, y, r);
}