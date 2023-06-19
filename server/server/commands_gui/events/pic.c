/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** pic.c
*/

#include "../../../include/my.h"

void send_pic_to_gui(this_t *this, int x, int y, char *id, list_players_t *list)
{
    list_players_t *tmp_gui = this->players;
    for (; tmp_gui; tmp_gui = tmp_gui->next) {
        if (tmp_gui->player->is_gui == true) {
            pic(this, tmp_gui->player, x, y, id, list);
            break;
        }
    }
}

void pic(this_t *this, player_t *player, int x, int y, char *id, list_players_t *list)
{
    dprintf(player->socket, "{\n\t\"cmd\": \"pic\",\n\t\"x\": %d,\n\t\"y\": %d,\n\t\"l\": \"%s\",", x, y, id);
    dprintf(player->socket, "\n\t\"n\": [\n");
    for (; list; list = list->next) {
        dprintf(player->socket, "\t\t{\n\t\t\t\"id\": \"%s\"\n\t\t}", list->player->id);
        if (list->next)
            dprintf(player->socket, ",\n");
    }
    dprintf(player->socket, "\n\t]\n}\n");
}
