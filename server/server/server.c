/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** server.c
*/

#include "../include/my.h"

void init_socket(this_t *this)
{
    this->control_socket = socket(AF_INET, SOCK_STREAM, 0);
    socket_error(this->control_socket);
    this->control_addr.sin_family = AF_INET;
    this->control_addr.sin_addr.s_addr = INADDR_ANY;
    this->control_addr.sin_port = htons(this->port);
    htons_error(this);
    int _bind = bind(this->control_socket, (SOCKADDR *)&this->control_addr, sizeof(this->control_addr));
    bind_error(_bind);
    int _listen = listen(this->control_socket, 42);
    listen_error(_listen);
}

void init_fdset(this_t *this)
{
    FD_ZERO(&this->readfds);
    FD_ZERO(&this->tmpfds);
    FD_SET(this->control_socket, &this->readfds);
}

void read_data(this_t *this, player_t *player, int i)
{
    int readValue = 0;
    char buffer[1024] = "\0";
    if ((readValue = read(player->socket, buffer, 1024)) == 0) {
        close(player->socket);
        FD_CLR(player->socket, &this->tmpfds);
        player->socket = 0;
    } else {
        this->cmd = NULL;
        char *tmp = strdup(buffer);
        this->cmd = strtok_wordtab(tmp, "  \t\n\r");
        commands(this, player);
    }
}

void data_from_player(this_t *this)
{
    list_players_t *tmp = this->players;
    for (int i = 0; tmp != NULL; i++, tmp = tmp->next) {
        if (FD_ISSET(tmp->player->socket, &this->tmpfds))
            read_data(this, tmp->player, i);
    }
}

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

void reset_timeout(this_t *this)
{
    double res = 1 / this->freq;
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

    while (1) {
        reset_timeout(this);
        this->tmpfds = this->readfds;
        add_player_to_set(this);

        // if (this->current_time - this->refill_map_timer >= (20 * this->freq)) {
        //     printf("Refill map\n");
        //     refill_map(this);
        //     this->refill_map_timer = this->current_time;
        // }


        // if (tmp != NULL && list_len_ai(tmp) == 1) {
        //     this->timeout->tv_sec = tmp->action->time_exec;
        //     this->timeout->tv_usec = 0;
        // }

        // if (this->timeout != NULL)
        //     printf("this->timeout->tv_sec: %ld\n", this->timeout->tv_sec);

        // list_cmd_ai_t *actions = this->actions;
        // list_players_t *players = this->players;

        // sleep(1);
        // printf("factions: %d\n", list_len_ai(this->first_actions));
        // if (this->first_actions != NULL) {
        //     this->timeout = malloc(sizeof(struct timeval));
        //     this->timeout->tv_sec = this->first_actions->action->time_exec;
        //     this->timeout->tv_usec = 0;
        // }

        _activity = select(this->maxfd + 1, &this->tmpfds, NULL, NULL, this->timeout);
        if (_activity)
            this->is_reset = false;


        select_error(_activity);
        handle_new_connection(this);
        data_from_player(this);

    }
}

void init_zappy_teams(this_t *this)
{
    this->teams = NULL;
    for (int i = 0; this->teams_name[i]; i++) {
        team_t *newteam = malloc(sizeof(team_t));
        newteam->name = this->teams_name[i];
        newteam->max_players = this->nb_clients;
        newteam->nb_players = 0;
        newteam->players_id = NULL;
        this->teams = add_element_team(this->teams, newteam, list_len_team(this->teams));
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

