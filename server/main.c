/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** main.c
*/

#include "include/my.h"

int main(int ac, char **av)
{
    this_t *this = malloc(sizeof(this_t));
    srand(time(NULL));
    this->refill_map_timer = time(NULL);
    if (ac > 11) {
        if (my_strcmp(av[1], "-help") == 0){
            display_help();
            return (0);
        }
        init_params(this);
        get_params(this, ac, av);
        run_server(this);
        return (0);
    }
    return (84);
}
