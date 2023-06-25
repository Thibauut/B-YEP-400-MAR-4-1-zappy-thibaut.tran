/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** edi.c
*/

#include "../../../include/my.h"

void send_edi_to_gui(this_t *this, char *uuid)
{
    list_players_t *tmp_gui = this->players;
    for (; tmp_gui; tmp_gui = tmp_gui->next) {
        if (tmp_gui->player->is_gui == true) {
            edi(this, tmp_gui->player, uuid);
            break;
        }
    }
}

void edi(this_t *this, player_t *player, char *uuid)
{
    char *response = malloc(sizeof(char) * 4096);
    response[0] = '\0';
    response = my_strcat(response, "{\n\t\"cmd\": \"edi\",\n\t\"id\": \"");
    response = my_strcat(response, uuid);
    response = my_strcat(response, "\"\n}\n");
    send(player->socket, response, strlen(response), 0);
    // dprintf(player->socket, "{\n\t\"cmd\": \"edi\",\n\t\"id\": \"%s\"\n}\n", uuid);
}
