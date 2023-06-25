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
    char *response = malloc(sizeof(char) * 4096);
    response[0] = '\0';
    response = my_strcat(response, "{\n\t\"cmd\": \"pic\",\n\t\"x\": ");
    response = my_strcat(response, my_itoa(x));
    response = my_strcat(response, ",\n\t\"y\": ");
    response = my_strcat(response, my_itoa(y));
    response = my_strcat(response, ",\n\t\"l\": \"");
    response = my_strcat(response, id);
    response = my_strcat(response, "\",\n\t\"n\": [\n");
    for (; list; list = list->next) {
        response = my_strcat(response, "\t\t{\n\t\t\t\"id\": \"");
        response = my_strcat(response, list->player->id);
        response = my_strcat(response, "\"\n\t\t}");
        if (list->next)
            response = my_strcat(response, ",\n");
    }
    response = my_strcat(response, "\n\t]\n}\n");
    send(player->socket, response, strlen(response), 0);
}
