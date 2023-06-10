/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** handle_connection.c
*/

#include "../include/my.h"

void add_player_to_set(this_t *this)
{
    list_players_t *tmp = this->players;
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->player->socket > 0) {
            FD_SET(tmp->player->socket, &this->tmpfds);
            (tmp->player->socket > this->maxfd) ?
                this->maxfd = tmp->player->socket : 0;
        }
    }
}

void new_player(this_t *this)
{
    list_players_t *tmp = this->players;
    for (int i = 0; tmp != NULL; i++, tmp = tmp->next) {
        if (tmp->player->socket == 0) {
            tmp->player->socket = this->new_socket;
            break;
        }
    }
}

player_t *create_player(this_t *this)
{
    player_t *newplayer = malloc(sizeof(player_t));
    newplayer->id = get_unique_uuid();
    newplayer->in_team = false;
    newplayer->socket = 0;
    newplayer->team = NULL;
    newplayer->level = 0;
    newplayer->is_gui = false;
    newplayer->x = rand() % this->width;
    newplayer->y = rand() % this->height;
    return (newplayer);
}

void handle_new_connection(this_t *this)
{
    if (FD_ISSET(this->control_socket, &this->tmpfds)) {
        socklen_t client_addr_len = sizeof(this->client_addr);
        if ((this->new_socket = accept(this->control_socket, (struct sockaddr *)&this->client_addr, &client_addr_len)) < 0) {
            perror("accept failed");
            exit(84);
        }
        player_t *newplayer = create_player(this);
        printf("New connection id: %s\n", newplayer->id);
        dprintf(this->new_socket, "Welcome to our Zappy server!\n");
        this->players = add_element(this->players, newplayer, 0);
        new_player(this);
    }
}
