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
    char *response = malloc(sizeof(char) * 4096);
    response[0] = '\0';
    response = my_strcat(response, "{\n\t\"cmd\": \"enw\",\n\t\"egg_id\": \"");
    response = my_strcat(response, egg->id);
    response = my_strcat(response, "\",\n\t\"player_id\": \"");
    response = my_strcat(response, egg->uuid_creator);
    response = my_strcat(response, "\",\n\t\"x\": ");
    response = my_strcat(response, my_itoa(egg->x));
    response = my_strcat(response, ",\n\t\"y\": ");
    response = my_strcat(response, my_itoa(egg->y));
    response = my_strcat(response, "\n}\n");
    send(player->socket, response, strlen(response), 0);
    // dprintf(player->socket, "{\n\t\"cmd\": \"enw\",\n\t\"egg_id\": \"%s\",\n\t\"player_id\": \"%s\",\n\t\"x\": %d,\n\t\"y\": %d\n}\n", egg->id, egg->uuid_creator, egg->x, egg->y);
}
