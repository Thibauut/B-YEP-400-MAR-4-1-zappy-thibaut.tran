/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** server.c
*/

#include "../include/my.h"

cmd_ai_t *get_action_by_id(this_t *this, char *uuid)
{
    list_cmd_ai_t *tmp = this->actions;
    cmd_ai_t *action = malloc(sizeof(cmd_ai_t));
    for (int index = 0; tmp != NULL; tmp = tmp->next, index += 1) {
        if (my_strcmp(tmp->action->uuid, uuid) == 0) {
            action = tmp->action;
            free_element_at_ai(this->actions, index);
            return (action);
        }
    }
}

void server_timer(this_t *this)
{
    double res = (double)1 / (double)this->freq;
    if (!this->timeout->tv_sec && !this->timeout->tv_usec) {
        this->is_reset = true;
        this->timeout->tv_sec = res;
        this->timeout->tv_usec = res * 1000000;
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

