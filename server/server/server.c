/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** server.c
*/

#include "../include/my.h"

list_teams_t *update_team(this_t *this, list_teams_t *tmp_teams, player_t *player)
{
    for (; tmp_teams; tmp_teams = tmp_teams->next) {
        if (my_strcmp(tmp_teams->team->name, player->team->name) == 0) {
            tmp_teams->team->nb_players -= 1;
            break;
        }
    }
    return tmp_teams;
}

void delete_player(this_t *this, player_t *player)
{
    list_players_t *tmp_players = this->players;
    list_teams_t *tmp_teams = this->teams;
    list_cmd_ai_t *tmp_cmd = this->actions;
    list_eggs_t *tmp_eggs = this->eggs;
    //supprimer les actions du joueur
    // for (int i = 0; tmp_cmd; tmp_cmd = tmp_cmd->next, i += 1) {
    //     if (my_strcmp(tmp_cmd->action->uuid, player->id) == 0)
    //         this->actions = free_element_at_ai(this->actions, i);
    // }
    //supprimer les oeufs du joueur
    for (int i = 0; tmp_eggs; tmp_eggs = tmp_eggs->next, i += 1) {
        if (my_strcmp(tmp_eggs->egg->uuid_creator, player->id) == 0) {
            send_edi_to_gui(this, tmp_eggs->egg->id);
            this->eggs = free_element_at_egg(this->eggs, i);
        }
    }
    //supprimer le joueur de la team
    this->teams = update_team(this, tmp_teams, player);
    //supprimer le joueur de la liste des joueurs
    for (int i = 0; tmp_players; tmp_players = tmp_players->next, i += 1) {
        if (tmp_players->player->is_gui == false && tmp_players->player->in_team == true
        && my_strcmp(tmp_players->player->id, player->id) == 0) {
            close(tmp_players->player->socket);
            tmp_players->player->socket = -1;
            this->players = free_element_at(this->players, i);
            break;
        }
    }
}

void update_player_life(this_t *this)
{
    list_players_t *tmp = this->players;

    for (; tmp; tmp = tmp->next) {
        if (tmp->player->in_team == true && tmp->player->life <= 0 && tmp->player->inventory->food <= 0) {
            send_pdi_to_gui(this, tmp->player->id);
            dprintf(tmp->player->socket, "dead\n");
            delete_player(this, tmp->player);
            return;
        }
        if (tmp->player->in_team == true && tmp->player->life <= 0 && tmp->player->inventory->food > 0) {
            tmp->player->life = 126;
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
    this->timeout->tv_sec = 0;
    this->timeout->tv_usec = 0;
    this->refill_map_timer = 0;
    this->is_start = false;
    this->players = NULL;
    int level = 0;
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
            list_players_t *tmp = this->players;
            for (; tmp != NULL; tmp = tmp->next)
                if (tmp->player->level > level)
                    level = tmp->player->level;
        }
        // printf("Highest level attained: lvl %d\n", level);
    }
    close(this->control_socket);
    free(this->timeout);
}

void run_server(this_t *this)
{
    init_socket(this);
    init_fdset(this);
    init_zappy_teams(this);
    init_zappy_map(this);
    this->eggs = NULL;
    this->nb_clients_egg = 0;
    server_loop(this);
}

