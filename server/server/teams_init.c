/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** init_team.c
*/

#include "../include/my.h"

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
    if (this->teams == NULL) {
        display_help();
        exit(84);
    }
}
