/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** server_timer.c
*/

#include "../include/my.h"

void server_timer(this_t *this)
{
    if (!this->timeout) {
        this->timeout = malloc(sizeof(struct timeval));
        this->timeout->tv_sec = 0;
        this->timeout->tv_usec = 0;
    }
    else {
        memset(this->timeout, 0, sizeof(struct timeval));
    }
    double min = 1;
    double freq = this->freq;
    double res = min / freq;
    if (!this->timeout->tv_sec && !this->timeout->tv_usec) {
        this->is_start = true;
        this->timeout->tv_sec = res;
        this->timeout->tv_usec = res * 1000000;
    }
}
