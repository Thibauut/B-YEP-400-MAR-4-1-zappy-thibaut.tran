/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** get_params.c
*/

#include "../../include/my.h"

void init_params(this_t *this)
{
    this->port = 0;
    this->width = 0;
    this->height = 0;
    this->nb_clients = 0;
    this->freq = 100;
}

void error_params(char**av, int i, int max_args, char *option, bool enable_max_args)
{
    int index = 0;
    for (; av[i + 1] != NULL && av[i + 1][0] != '-'; i += 1, index += 1) {
        if (index >= max_args && enable_max_args == true) {
            printf("too many arguments for %s option.\n", option);
            exit(84);
        }
    }
    if (index == 0) {
        printf("missing value for %s option.\n", option);
        exit(84);
    }
}

void get_port(this_t *this, char *port)
{
    if (my_is_number(port) == 1) {
        printf("-p invalid port \'%s\'\n", port);
        exit(84);
    }
    this->port = atoi(port);
    if (this->port < 0 || this->port > 65535) {
        printf("-p invalid port \'%d'\n", this->port);
        exit(84);
    }
}

void get_width(this_t *this, char *width)
{
    if (my_is_number(width) == 1) {
        printf("-x invalid width \'%s\'\n", width);
        exit(84);
    }
    this->width = atoi(width);
    if (this->width < 10 || this->width > 30) {
        printf("-x option only accepts integer values between 10 and 30\n");
        exit(84);
    }
}

void get_height(this_t *this, char *height)
{
    if (my_is_number(height) == 1) {
        printf("-y invalid height \'%s\'\n", height);
        exit(84);
    }
    this->height = atoi(height);
    if (this->height < 10 || this->height > 30) {
        printf("-y option only accepts integer values between 10 and 30\n");
        exit(84);
    }
}

void get_teams(this_t *this, char **av, int i)
{
    int j = 0;
    this->teams_name = malloc(sizeof(char *) * (i + 1));
    for (; av[i + 1] != NULL && av[i + 1][0] != '-'; i += 1, j += 1)
        this->teams_name[j] = strdup(av[i + 1]);
    this->teams_name[j] = NULL;
}

void get_nb_clients(this_t *this, char *nb_clients)
{
    if (my_is_number(nb_clients) == 1) {
        printf("-c invalid nb_clients \'%s\'\n", nb_clients);
        exit(84);
    }
    this->nb_clients = atoi(nb_clients);
    if (this->nb_clients < 1) {
        printf("-c invalid nb_clients \'%d\'\n", this->nb_clients);
        exit(84);
    }
}

void get_freq(this_t *this, char *freq)
{
    if (my_is_number(freq) == 1) {
        printf("-f invalid frequence \'%s\'\n", freq);
        exit(84);
    }
    this->freq = atoi(freq);
    if (this->freq < 2 || this->freq > 10000) {
        printf("-f option only accepts integer values between 2 and 10000\n");
        exit(84);
    }
}

void get_params(this_t *this, int ac, char **av)
{
    int err = 0;
    for (int i = 0; av[i]; i += 1) {
        if (my_strcmp(av[i], "-p") == 0) {
            error_params(av, i, 1, "-p", true);
            get_port(this, av[i + 1]);
        }
        if (my_strcmp(av[i], "-x") == 0) {
            error_params(av, i, 1, "-x", true);
            get_width(this, av[i + 1]);
        }
        if (my_strcmp(av[i], "-y") == 0) {
            error_params(av, i, 1, "-y", true);
            get_height(this, av[i + 1]);
        }
        if (my_strcmp(av[i], "-n") == 0) {
            error_params(av, i, 0, "-n", false);
            get_teams(this, av, i);
        }
        if (my_strcmp(av[i], "-c") == 0) {
            error_params(av, i, 1, "-c", true);
            get_nb_clients(this, av[i + 1]);
        }
        if (my_strcmp(av[i], "-f") == 0) {
            error_params(av, i, 1, "-f", true);
            get_freq(this, av[i + 1]);
        }
    }
    team_t *team = malloc(sizeof(team_t));
    for (int i = 0; this->teams_name[i]; i += 1) {
        team->name = strdup(this->teams_name[i]);
        team->max_players = this->nb_clients;
        team->nb_players = 0;
        this->teams = add_element_team(this->teams, team, 0);
    }
}
