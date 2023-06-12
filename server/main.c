/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** main.c
*/

#include "include/my.h"

void get_current_time(this_t *this)
{
    time_t start = time(NULL), now;
    while (1) {
        now = time(NULL);
        if (now - start >= 1) {
            start = now;
            this->current_time += 1;
        }
    }
}

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

        // pthread_create(&this->thread_timer, NULL, (void *(*)(void *))get_current_time, this);
        // pthread_create(&this->thread_server, NULL, (void *(*)(void *))run_server, this);
        // pthread_join(this->thread_timer, NULL);
        // pthread_join(this->thread_server, NULL);
        return (0);
    }
    return (84);
}
