/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** tna.c
*/

#include "../../include/my.h"

void tna(this_t *this, player_t *player)
{
    if (this->cmd[1] != NULL) {
        dprintf(player->socket, "ko\n");
        return;
    }
    char *response = malloc(sizeof(char) * 4096);
    response[0] = '\0';
    response = my_strcat(response, "{\n\t\"cmd\": \"tna\",\n\t\"teams\": [\n");

    list_teams_t *tmp = this->teams;
    for (; tmp != NULL; tmp = tmp->next) {
        response = my_strcat(response, "\t\t{\n\t\t\t\"name\": \"");
        response = my_strcat(response, tmp->team->name);
        response = my_strcat(response, "\"\n\t\t}");
        if (tmp->next != NULL) {
            response = my_strcat(response, ",\n");
        }
    }
    response = my_strcat(response, "\n\t]\n}");
    dprintf(player->socket, "%s\n", response);
}
