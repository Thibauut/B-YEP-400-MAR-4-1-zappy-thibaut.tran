/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** server_timer.c
*/

#include "../include/my.h"

void server_timer(this_t *this)
{
    double res = (double)1.0 / (double)this->freq;
    if (!this->timeout->tv_sec && !this->timeout->tv_usec) {
        this->is_start = true;
        this->timeout->tv_sec = res;
        this->timeout->tv_usec = res * 10000000;
    }
}
