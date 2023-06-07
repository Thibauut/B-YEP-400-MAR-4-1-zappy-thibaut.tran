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
    while (1) {
        this->tmpfds = this->readfds;
        time_t current_time = time(NULL);
        if (current_time - this->start_time >= (20 * this->freq)) {
            refill_map(this);
            this->start_time = current_time;
        }

        add_player_to_set(this);
        _activity = select(this->maxfd + 1, &this->tmpfds, NULL, NULL, &(this->timeout));
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

