/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** get_params.c
*/

#include "../../include/my.h"

void init_params(this_t *this)
{
    this->port = 4242;
    this->width = 10;
    this->height = 10;
    this->nb_clients = 3;
    this->nb_clients_egg = 0;
    this->freq = 100;
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

void get_teams(this_t *this, char **av)
{
    int j = 0;
    int i = 0;
    for (; av[i] != NULL && my_strcmp(av[i], "-n") != 0; i += 1);
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
    for (int opt = 0, opterr = 0; (opt = getopt(ac, av, "p:x:y:n:c:f:")) > 0;) {
        if (opt == 'p')
            get_port(this, optarg);
        if (opt == 'x')
            get_width(this, optarg);
        if (opt == 'y')
            get_height(this, optarg);
        if (opt == 'n')
            get_teams(this, av);
        if (opt == 'c')
            get_nb_clients(this, optarg);
        if (opt == 'f')
            get_freq(this, optarg);
        if (opt == '?') {
            display_help();
            exit(84);
        }
    }
    if (this->teams_name == NULL) {
        display_help();
        exit(84);
    }
}


