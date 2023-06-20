/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** server.c
*/

#include "../include/my.h"

void update_player_life(this_t *this)
{
    list_players_t *tmp = this->players;
    for (int index = 0; tmp; tmp = tmp->next, index += 1) {
        if (tmp->player->in_team == true && tmp->player->life <= 0 && tmp->player->inventory->food <= 0) {
            send_pdi_to_gui(this, tmp->player->id);
            dprintf(tmp->player->socket, "dead\n");
            this->players = free_element_at(this->players, index);
            this->teams->team->nb_players -= 1;
            break;
        }
        if (tmp->player->in_team == true && tmp->player->life <= 0 && tmp->player->inventory->food > 0) {
            tmp->player->life = 1260 / this->freq;
            tmp->player->inventory->food -= 1;
        }
        if (tmp->player->in_team == true)
            tmp->player->life -= 1;
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
    this->is_start = false;

    while (1) {
        server_timer(this);
        this->tmpfds = this->readfds;
        add_player_to_set(this);
        _activity = select(this->maxfd + 1, &this->tmpfds, NULL, NULL, this->timeout);
        select_error(this, _activity);
        handle_new_connection(this);
        data_from_player(this);

        if (this->is_start == true) {
            exec_actions(this);
            update_map(this);
            update_player_life(this);
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

