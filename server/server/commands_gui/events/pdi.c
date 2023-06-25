/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** pdi.c
*/

#include "../../../include/my.h"

void send_pdi_to_gui(this_t *this, char *uuid)
{
    list_players_t *tmp_gui = this->players;
    for (; tmp_gui; tmp_gui = tmp_gui->next) {
        if (tmp_gui->player->is_gui == true) {
            pdi(this, tmp_gui->player, uuid);
            break;
        }
    }
}

void pdi(this_t *this, player_t *player, char *dead_id)
{
    char *response = malloc(sizeof(char) * 4096);
    response[0] = '\0';
    response = my_strcat(response, "{\n\t\"cmd\": \"pdi\",\n\t\"id\": \"");
    response = my_strcat(response, dead_id);
    response = my_strcat(response, "\"\n}\n");
    send(player->socket, response, strlen(response), 0);
}
