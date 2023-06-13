/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** server.c
*/

#include "../include/my.h"

player_t *get_player_by_uuid(this_t *this, char *uuid)
{
    player_t *player = malloc(sizeof(player_t));
    for (list_players_t *tmp = this->players; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->player->id, uuid) == 0) {
            player = tmp->player;
            return player;
        }
    }
}

void exec_actions(this_t *this)
{
    list_cmd_ai_t *tmp = this->actions;
    for (int i = 0; tmp != NULL; tmp = tmp->next, i += 1) {
        if (tmp->action->duration <= 0) {
            exec_ai_commands(this, get_player_by_uuid(this, tmp->action->uuid), 1);
            this->actions = free_element_at_ai(this->actions, i);
            return;
        }
        tmp->action->duration -= 1;
    }
}

void server_loop(this_t *this)
{
    int _activity;
    this->maxfd = this->control_socket;
    printf("Server running on port: %d\n", this->port);
    this->actions = NULL;
    this->timeout = malloc(sizeof(struct timeval));
    this->refill_map_timer = 0;
    this->is_reset = false;

    while (1) {
        server_timer(this);
        this->tmpfds = this->readfds;
        add_player_to_set(this);

        _activity = select(this->maxfd + 1, &this->tmpfds, NULL, NULL, this->timeout);
        select_error(this, _activity);
        handle_new_connection(this);
        data_from_player(this);

        if (this->is_reset == true) {
            exec_actions(this);
            update_map(this);
        }
    }
}

void run_server(this_t *this)
{
    init_socket(this);
    init_fdset(this);
    init_zappy_teams(this);
    init_zappy_map(this);
    server_loop(this);
}

