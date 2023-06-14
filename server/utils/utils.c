/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** utils.c
*/

#include "../include/my.h"

int my_is_number(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return (1);
    }
    return (0);
}

char *my_strlowcase(char *str)
{
    char *tmp = malloc(sizeof(char) * my_strlen(str) + 1);
    for (int a = 0; str[a] != '\0'; a++) {
        if (str[a] >= 65 && str[a] <= 90) {
            tmp[a] = (str[a] + 32);
            continue;
        }
        tmp[a] = str[a];
    }
    return (tmp);
}

int my_strcasecmp(char *s1, char *s2)
{
    s1 = my_strlowcase(s1);
    s2 = my_strlowcase(s2);
    int len = my_strlen(s2);
    if (len != my_strlen(s1))
        return (1);
    for (int j = 0; j != len; j += 1) {
        if (s1[j] != s2[j])
            return (1);
    }
    return (0);
}

int my_strlen(char *str)
{
    int i = 0;
    for (; str[i]; i += 1);
    return i;
}

char **strtok_wordtab(char *str, char *tok)
{
    if ((str == NULL) ||
    (strspn(str, " \t\r\n") == (size_t)my_strlen(str)) || (tok == NULL)) {
        char **tmp = malloc(sizeof(char *) * 1);
        tmp[0] = strdup("\n");
        return (tmp);
    }
    char **tab = malloc(sizeof(char *) * 4096);
    char *tmp = strtok(str, tok);
    int i = 0;
    for (; tmp != NULL; i++) {
        tab[i] = strdup(tmp);
        tmp = strtok(NULL, tok);
    }
    tab[i] = NULL;
    return (tab);
}

char *my_strcat(char *dest, char *src)
{
    int a = 0, i = 0;
    char *tmp = malloc(sizeof(char) *
    ((my_strlen(dest) + my_strlen(src)) + 1));
    for (; dest[a] != '\0'; a += 1)
        tmp[a] = dest[a];
    for (; src[i] != '\0'; i += 1)
        tmp[a + i] = src [i];
    tmp[a + i] = '\0';
    return (tmp);
}

int my_strcmp(char *s1, char *s2)
{
    int len = my_strlen(s2);
    if (len != my_strlen(s1))
        return (1);
    for (int j = 0; j != len; j += 1) {
        if (s1[j] != s2[j])
            return (1);
    }
    return (0);
}

int create_tab(char *str, char c)
{
    int i = 0, j = 0;
    for (; str[i] != 0; i += 1) {
        if (str[i] == c)
            j += 1;
    }
    return (j + 1);
}

char **word_to_tab(char *str, char c, int i)
{
    int j = 0, k = 0, size = create_tab(str, c);
    char **tab = malloc(sizeof(char *) * (size + 1));
    tab[0] = malloc(sizeof(char) * (my_strlen(str) + 1));
    while (str[i] != '\0') {
        if (str[i] == c) {
            i += 1;
            tab[j][k] = '\0';
            j += 1, k = 0;
            tab[j] = malloc(sizeof(char) * (my_strlen(str) + 1));
        }
        tab[j][k] = str[i];
        i += 1, k += 1;
    }
    j += 1, tab[j] = 0;
    tab[j - 1][k - 1] = '\0';
    return (tab);
}

char *my_itoa(int nb)
{
    int size = 0;
    char *nb_in_str = NULL;
    int tmp = nb;
    if (tmp == 0)
        size = 1;
    while (tmp > 0) {
        tmp /= 10;
        size++;
    }
    nb_in_str = malloc(sizeof(char) * (size + 1));
    nb_in_str[size] = '\0';
    while (size--) {
        nb_in_str[size] = nb % 10  + '0';
        nb /= 10;
    }
    return (nb_in_str);
}

char *get_unique_uuid(void)
{
    uuid_t binuuid;
    char *uuid = malloc(sizeof(char) * 37);
    uuid_generate_random(binuuid);
    uuid_unparse_upper(binuuid, uuid);
    return (uuid);
}

struct timeval float_to_timeval(float seconds)
{
    struct timeval tv;
    long int microseconds = seconds * 1000000;
    tv.tv_sec = microseconds / 1000000;
    tv.tv_usec = microseconds % 1000000;
    return tv;
}

player_t *get_player_by_uuid(this_t *this, char *uuid)
{
    player_t *player = malloc(sizeof(player_t));
    for (list_players_t *tmp = this->players; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->player->id, uuid) == 0) {
            player = tmp->player;
            return player;
        }
    }
}
