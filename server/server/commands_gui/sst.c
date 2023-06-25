/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** sst.c
*/

#include "../../include/my.h"

void sst(this_t *this, player_t *player)
{
    if (this->cmd[1] == NULL) {
        dprintf(player->socket, "ko\n");
        return;
    }
    if (my_is_number(this->cmd[1]) == 1) {
        dprintf(player->socket, "ko\n");
        return;
    }
    this->freq = atoi(this->cmd[1]);

    char *response = malloc(sizeof(char) * 4096);
    response[0] = '\0';
    response = my_strcat(response, "{\n\t\"cmd\": \"sst\",\n\t\"f\": ");
    response = my_strcat(response, my_itoa(this->freq));
    response = my_strcat(response, "\n}\n");
    send(player->socket, response, strlen(response), 0);
}
