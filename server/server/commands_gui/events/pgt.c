/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** pgt.c
*/

#include "../../../include/my.h"

void send_pgt_to_gui(this_t *this, char *take_id, int resource)
{
    list_players_t *tmp_gui = this->players;
    for (; tmp_gui; tmp_gui = tmp_gui->next) {
        if (tmp_gui->player->is_gui == true) {
            pgt(this, tmp_gui->player, take_id, resource);
            break;
        }
    }
}

void pgt(this_t *this, player_t *player, char *take_id, int resource)
{
    char *response = malloc(sizeof(char) * 4096);
    response[0] = '\0';
    response = my_strcat(response, "{\n\t\"cmd\": \"pgt\",\n\t\"id\": \"");
    response = my_strcat(response, take_id);
    response = my_strcat(response, "\",\n\t\"resource\": ");
    response = my_strcat(response, my_itoa(resource));
    response = my_strcat(response, "\n}\n");
    send(player->socket, response, strlen(response), 0);
}
