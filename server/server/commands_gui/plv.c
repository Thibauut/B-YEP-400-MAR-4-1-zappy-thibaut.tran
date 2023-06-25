/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** plv.c
*/

#include "../../include/my.h"

void plv(this_t *this, player_t *player)
{
    if (this->cmd[1] == NULL) {
        dprintf(player->socket, "ko\n");
        return;
    }
    list_players_t *tmp = this->players;
    for (; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->player->id, this->cmd[1]) == 0 && tmp->player->in_team == true) {
            char *response = malloc(sizeof(char) * 4096);
            response[0] = '\0';
            response = my_strcat(response, "{\n\t\"cmd\": \"plv\",\n\t\"id\": \"");
            response = my_strcat(response, tmp->player->id);
            response = my_strcat(response, "\",\n\t\"level\": ");
            response = my_strcat(response, my_itoa(tmp->player->level));
            response = my_strcat(response, "\n}\n");
            send(player->socket, response, strlen(response), 0);
            return;
        }
    }
    dprintf(player->socket, "ko\n");
}