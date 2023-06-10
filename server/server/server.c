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
        this->players = free_element_at(this->players, i);
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

void server_loop(this_t *this)
{
    int _activity;
    this->maxfd = this->control_socket;
    printf("Server running on port: %d\n", this->port);

    this->actions = NULL;
    this->timeout = NULL;

    this->start_time = time(NULL);
    this->curr_time = 0;
    while (1) {
        this->tmpfds = this->readfds;
        this->current_time = time(NULL);

        if (this->current_time - this->refill_map_timer >= (20 * this->freq)) {
            printf("Refill map\n");
            refill_map(this);
            this->refill_map_timer = this->current_time;
        }
        // if (this->current_time - this->start_time >= 1 && this->actions != NULL) {
        //     this->start_time = this->current_time;
        //     this->curr_time += 1;
        //     printf("this->curr_time: %d\n", this->curr_time);
        // }

        add_player_to_set(this);
        _activity = select(this->maxfd + 1, &this->tmpfds, NULL, NULL, this->timeout);
        select_error(_activity);
        handle_new_connection(this);
        data_from_player(this);





        if (_activity == 0) {
            // printf("Dead\n");
            // list_cmd_ai_t *tmp_action = this->actions;
            // list_players_t *tmp_player = this->players;

            // if (tmp_action == NULL)
            //     this->timeout = NULL;
            // else {
            //     // for (; tmp_action != NULL; tmp_action = tmp_action->next) {
            //     //     for (int i = 0; tmp_player != NULL; tmp_player = tmp_player->next, i += 1) {
            //     //         if (my_strcmp(tmp_player->player->id, tmp_action->action->uuid)) {
            //     //             this->players = free_element_at(this->players, i);
            //     //             close(tmp_player->player->socket);
            //     //             break;
            //     //         }
            //     //     }
            //     // }
            //     if (tmp_action != NULL) {
            //         tmp_action = free_element_at_ai(tmp_action, 0);
            //         this->timeout->tv_sec = tmp_action->action->time_exec;
            //     }
            // }
        }
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

